from .bot_configuration import aliases, safeids, add_safeid, write_safeids, add_alias
from .bot_message import unpermitted


from os import getenv, path
from json import loads


homedir = path.join(getenv('HOME'), 'Bots', 'Takamaki')
commandlist = {}


async def add_command(command, function, trusted=None):
    if trusted is None:
        trusted = False

    if command not in commandlist.keys():
        commandlist.update({command: {'function': function, 'trusted': trusted}})
        return True

    return False


async def remove_command(command):
    if command in commandlist.keys():
        del commandlist[command]
        return True

    return False


async def call_command(command, message, numargs, *args):
    if message.author.bot:
        return None

    if command in commandlist.keys():
        if message.author.id not in safeids and commandlist[command]['trusted']:
            await unpermitted(message)
            return None

        func = commandlist[command]['function']

        if numargs == 3:
            content, searcher = args
            await func(message, content, searcher)
        else:
            await func(message)

    return None


async def init():
    safeidsfile = path.join(homedir, 'program', 'configs', 'safeids.json')
    aliasesfile = path.join(homedir, 'program', 'configs', 'aliases.json')

    if path.isfile(safeidsfile):
        with open(safeidsfile, 'r') as r:
            idjson = loads(r.read())

        for id in idjson['safe_ids']:
            add_safeid(int(id))
    else:
        add_safeid()
        write_safeids()

    if path.isfile(aliasesfile):
        with open(aliasesfile, 'r') as r:
            aliasjson = loads(r.read())

        for key, val in aliasjson.items():
            add_alias(key, val)

    print('Anne Takamaki is ready...')
