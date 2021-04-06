from os import makedirs, getenv, unlink, path
from json import dumps, loads
from datetime import datetime
from html import unescape
from random import choice
from hashlib import md5
from . import Request


headers = {
    'host': 'chan.sankakucomplex.com',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0',
    'cookie': 'locale=en; auto_page=0; hide-news-ticker=1',
    'cache-control': 'max-age=0',
    'dnt': '1',
    'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
    'accept-encoding': 'gzip, deflate, br',
    'upgrade-insecure-requests': '1'
}


def get_image(posts=None):
    if posts is None:
        return None

    post = choice(posts)
    url = f'https://chan.sankakucomplex.com{post}'

    request = Request(url, headers)
    links = request.get(r'<li>Original: <a href="(.*?)" id=highres')

    if links is not None:
        try:
            if links[1] == 429:
                return links
        except:
            pass

        for link in links:
            request = Request(unescape(f'https:{link}'), headers)
            bindata = request.binget()

            try:
                if bindata[1] == 429:
                    return bindata
            except:
                pass

            if bindata is None or len(bindata) == 0:
                return None

            cachedir = path.join(getenv('HOME'), 'Bots', 'Takamaki', 'program', 'cache')
            if not path.exists(cachedir):
                makedirs(cachedir)

            cachefile = path.join(cachedir, link.split('/')[-1].split('?')[0])

            file = open(cachefile, 'wb')
            file.write(bindata)
            file.close()

            file = open(cachefile, 'rb')
            return {'file': file, 'filename': cachefile}

    return None


def search(term, next=None, posts=None, recurse=None):
    if posts is None:
        posts = []

    if recurse is None:
        recurse = 26

    cachepath = path.join(getenv('HOME'), 'Bots', 'Takamaki', 'program', 'cache')
    cachefile = path.join(cachepath, f'{md5(term.encode()).hexdigest()}.json')

    if not path.exists(cachepath):
        makedirs(cachepath)

    today = datetime.today()
    timestamp = int(datetime(today.year, today.month, today.day, 0, 0, 0, 0).timestamp())

    if not path.isfile(cachefile):
        url = f'https://chan.sankakucomplex.com/post/index.content?next={next}&tags={term}' if next is not None else \
            f'https://chan.sankakucomplex.com/post/index.content?tags={term}'

        if recurse > 0:
            request = Request(url, headers)
            links = request.get(r'<a href="(.*?)" ')

            if links is not None:
                try:
                    if links[1] == 429:
                        return links
                except:
                    pass

                for link in links:
                    posts.append(link)

                pivot = posts.pop().split('/')[-1]
                search(term, pivot, posts, recurse - 1)

        jsondata = {'posts': posts, 'exp': timestamp + 604800}
        with open(cachefile, 'w') as cachedata:
            cachedata.write(dumps(jsondata))

        return jsondata

    with open(cachefile, 'r') as cachedata:
        jsondata = loads(cachedata.read())

    if jsondata['exp'] <= timestamp:
        unlink(cachefile)
        search(term, next, posts)

    return jsondata
