from SimpleRequests import SimpleRequest

if __name__ == '__main__':
    simplerequest = SimpleRequest()
    data = simplerequest.request.grab_page('https://discordapp.com/api/v6/invite/discord-testers')

    print(data)
