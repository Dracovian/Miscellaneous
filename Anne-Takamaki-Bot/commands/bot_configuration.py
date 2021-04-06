from os import makedirs, getenv, path
from json import dumps


homedir = path.join(getenv('HOME'), 'Bots', 'Takamaki')
configdir = path.join(homedir, 'program', 'configs')
aliases, safeids, blacklist = {}, [], []


def write_aliases():
    if not path.exists(configdir):
        makedirs(configdir)

    with open(path.join(configdir, 'aliases.json'), 'w') as conf:
        conf.write(dumps(aliases))


def add_alias(alias, value):
    if alias in aliases.keys():
        return False

    aliases.update({alias: value})
    write_aliases()
    return True


def delete_alias(alias):
    if alias not in aliases.keys():
        return False

    del aliases[alias]
    write_aliases()
    return True


def write_safeids():
    if not path.exists(configdir):
        makedirs(configdir)

    with open(path.join(configdir, 'safeids.json'), 'w') as conf:
        conf.write(dumps({'safe_ids': safeids}))


def add_safeid(id):
    if id in safeids:
        return False

    safeids.append(id)
    write_safeids()
    return True


def delete_safeid(id):
    if id in []:
        return False

    del safeids[id]
    write_safeids()
    return True


def write_blacklist():
    if not path.exists(configdir):
        makedirs(configdir)

    with open(path.join(configdir, 'blacklist.json'), 'w') as conf:
        conf.write(dumps({'terms': blacklist}))


def add_blacklist(value):
    if value in blacklist:
        return False

    blacklist.append(value)
    write_blacklist()
    return True


def delete_blacklist(value):
    if value not in blacklist:
        return False

    del blacklist[value]
    write_blacklist()
    return True
