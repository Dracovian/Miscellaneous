from http.client import HTTPSConnection, HTTPConnection
from re import findall as regex
from time import sleep
from sys import stderr
sleeptime = 0


class Request:
    def __init__(self, url, headers=None):
        if headers is None:
            headers = {}

        splices = url.split('/')
        scheme = splices[0][:-1]

        self.url     = url
        self.connect = HTTPSConnection if scheme == 'https' else HTTPConnection
        self.domain  = splices[2].split(':')[0]
        self.port    = splices[2].split(':')[1] if len(splices[2].split(':')) == 2 else 443 if scheme == 'https' else 80
        self.urlpath = f"/{'/'.join(splices[3::])}"

        headers.update({'host': self.domain})
        self.headers = headers
        sleep(sleeptime)

    def binget(self):
        try:
            conn = self.connect(self.domain, self.port)
            conn.request('GET', self.urlpath, headers=self.headers)

            resp = conn.getresponse()
            filesize = int(resp.getheader('Content-Length'))

            if filesize == 0 or filesize > 8388608:
                return None

            if 199 < resp.status < 300:
                return resp.read()
            if 299 < resp.status < 400:
                new = resp.getheader('Location')

                request = Request(new, self.headers)
                return request.binget()

            if resp.status == 429:
                return f'We are currently being ratelimited, retry after {resp.getheader("Retry-After")} seconds.', 429

            raise BaseException(f'HTTP {resp.status}: {resp.reason} on {self.url}')
        except BaseException as bex:
            stderr.write(f'{bex}\n')
            return None

    def get(self, scan):
        try:
            conn = self.connect(self.domain, self.port)
            conn.request('GET', self.urlpath, headers=self.headers)

            resp = conn.getresponse()
            if 199 < resp.status < 300:
                return regex(scan, resp.read().decode())
            if 299 < resp.status < 400:
                new = resp.getheader('location')

                request = Request(new, self.headers)
                return request.get(scan)

            if resp.status == 429:
                return f'We are currently being ratelimited, retry after {resp.getheader("Retry-After")} seconds.', 429

            raise BaseException(f'HTTP {resp.status}: {resp.reason}')
        except BaseException as bex:
            stderr.write(f'{bex}\n')
            return None
