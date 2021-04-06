from http.client import HTTPConnection, HTTPSConnection
from os import path, getcwd, makedirs
from urllib.parse import unquote
from re import findall
from json import loads
from sys import stderr

if not path.exists(path.join(getcwd(), 'media')):
    makedirs(path.join(getcwd(), 'media'))
    
host, port, sub, sort = 'gateway.reddit.com', 443, '', 'new'
contents = []

newfile = lambda url: path.join(getcwd(), 'media', '{}_{}'.format(replacer(url.split('/')[-2]), url.split('/')[-1].split('?')[0]))
splicer = lambda url: [url.split('/')[2], 443 if url.split('/')[0] == 'https:' else 80, '/{}'.format('/'.join(url.split('/')[3::]))]

headerd = {'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36'}

def replacer(input):
    for ch in ['\\', '/', ':', '*', '?', '"', '<', '>', '|']:
        input = input.replace(ch, '')

    return input

def log(error):
    stderr.write('Error logged: {}\n'.format(error))
    with open('error.log', 'a') as errlog:
        errlog.write(error)

def download(filename, rhost, rport, rloc):
    with open(filename, 'wb') as rawData:
        conn = HTTPSConnection(rhost, 443) if rport == 443 else HTTPConnection(rhost, 80)
        conn.request('GET', rloc)

        resp = conn.getresponse()
        if resp.status == 200:
            rawData.write(resp.read())
        else:
            log('Failed to grab data from {}'.format(rloc))

def downloader():
    for content in contents:
        filename = newfile(content)
        rhost, rport, rloc = splicer(content)
        
        if rhost == 'www.redditmedia.com':
            conn = HTTPSConnection(rhost, 443) if rport == 443 else HTTPConnection(rhost, 80)
            conn.request('GET', rloc)

            resp = conn.getresponse()
            if resp.status == 200:
                images = findall(r'image\=(.*?)\"', resp.read().decode('utf-8'))
                for image in images:
                    filename = newfile(unquote(image))
                    rhost, rport, rloc = splicer(unquote(image))

                    if rhost == 'i.imgur.com':
                        filename = path.join(getcwd(), 'media', 'i.imgur.com_{}.jpg'.format(path.split(filename)[-1]))

                    if rhost == 'thumbs.gfycat.com':
                        rhost = 'gfycat.com'
                        rloc = rloc.replace('-size_restricted', '').split('&')[0]

                        conn = HTTPSConnection(rhost, 443) if rport == 443 else HTTPConnection(rhost, 80)
                        conn.request('GET', rloc)

                        resp = conn.getresponse()
                        if resp.status == 200:
                            files = findall(r'src\=\"(.*?)\" type\=\"video/mp4"', resp.read().decode('utf-8'))
                            for file in files:
                                file = file.split('"')[-1]
                                filename = newfile(file)
                                rhost, rport, rloc = splicer(file)
                        else:
                            log('Failed to grab data from {}'.format(content))

                    download(filename, rhost, rport, rloc)
            else:
                log('Failed to grab data from {}'.format(content))
        else:
            download(filename, rhost, rport, rloc)

def paginate(lastPostId):
    conn = HTTPSConnection(host, port)
    conn.request('GET', '/desktopapi/v1/subreddits/{}?rtj=only&redditWebClient=web2x&app=web2x-client-production&after={}&dist=12&layout=card&sort={}&allow_over18=1&include=prefsSubreddit'.format(sub, lastPostId, sort), headers=headerd)

    resp = conn.getresponse()
    if resp.status == 200:
        j = loads(resp.read())
        postIds = j['postIds']

        for postId in postIds:
            try:
                post = j['posts'][postId]['media']['content']
                contents.append(post)
            except Exception:
                continue
        try:
            paginate(postIds[-1])
        except Exception:
            print('Found {} files.'.format(len(contents)))
            downloader()
    else:
        print(resp.status, resp.reason)

if __name__ == '__main__':
    conn = HTTPSConnection(host, port)
    conn.request('GET', '/desktopapi/v1/subreddits/{}?rtj=only&redditWebClient=web2x&app=web2x-client-production&dist=12&layout=card&sort={}&allow_over18=1&include=prefsSubreddit'.format(sub, sort), headers=headerd)

    resp = conn.getresponse()
    if resp.status == 200:
        j = loads(resp.read())
        postIds = j['postIds']

        for postId in postIds:
            try:
                post = j['posts'][postId]['media']['content']
                contents.append(post)
            except Exception:
                continue

        paginate(postIds[-1])
    else:
        print(resp.status, resp.reason)
