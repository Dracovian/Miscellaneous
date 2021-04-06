from .bot_configuration import add_alias, delete_alias, add_blacklist, delete_blacklist, add_safeid, delete_safeid, blacklist, aliases
from .bot_message import check_permission, bot_send_message, bot_send_error, botmessages
from .scripts.sankakucomplex import get_image, search
from . import homedir, commandlist


from os import unlink, path
from hashlib import md5
import discord


async def bot_clear_cache(message, content, command):
    if await check_permission(message):
        request = content.replace(command, '')
        request = '_'.join(request.split(' ')[::-1])
        encoded = f'{md5(request.encode()).hexdigest()}.json'

        cachefile = path.join(homedir, 'program', 'cache', encoded)
        if path.isfile(cachefile):
            unlink(cachefile)
            await bot_send_message(message, f'Cleaned cache file for `{request}`')


async def bot_clear_messages(message):
    if await check_permission(message):
        for msg in botmessages:
            await msg.delete()

        del botmessages[:]


async def bot_add_trust(message, content, command):
    if await check_permission(message):
        request = content.replace(command, '')
        request = request[3:-1]

        add_safeid(int(request))
        await bot_send_message(message, f'User `{request}` is now trusted!')


async def bot_delete_trust(message, content, command):
    if await check_permission(message):
        request = content.replace(command, '')
        request = request[3:-1]

        delete_safeid(int(request))
        await bot_send_message(message, f'User `{request}` is no longer trusted!')


async def bot_add_alias(message, content, command):
    if await check_permission(message):
        request = content.replace(command, '')
        request = request.split(' ')

        if not add_alias(request[0], f'i want to see some {request[1]}'):
            await bot_send_error(message, f'Alias `{request[0]}` already exists!')
            return None

        await bot_send_message(message, f'`{request[0]}` is now an alias for `{aliases[request[0]]}`')


async def bot_delete_alias(message, content, command):
    if await check_permission(message):
        request = content.replace(command, '')

        if not delete_alias(request):
            await bot_send_error(message, f'Alias `{request}` does not exist!')
            return None

        await bot_send_message(message, f'`{request}` is no longer an alias')


async def bot_list_aliases(message):
    msg = '**Registered Aliases:**\n```Aliased Functions:\n'
    if len(aliases) > 0:
        for key, value in aliases.items():
            msg += f'{key} = {value}\n'
    else:
        msg += 'There are no aliases registered at the moment.'

    msg += '```'
    await message.channel.send(msg)


async def bot_list_functions(message):
    msg = '''**Functions List:**
```
    Non-Privileged Functions:
        - i want to see some {noun} : Grab a random image or video pertaining to {noun}
        - i want to see the aliases : Print out the list of registered aliases
        - i want some help          : Print out this list of functions
        
    Privileged (Trusted) Functions:
        - i want to clear the cache for {noun}       : Clear the local data cache for {noun}
        - i want you to clean up                     : Force the bot to delete some of its messages
        - i want to trust {member}                   : Add {member} to the trusted list
        - i want to untrust {member}                 : Remove {member} from the trusted list
        - i want to alias {alias} {noun}             : Create an alias for {noun} set to {alias}
        - i want to dealias {alias}                  : Remove an alias named {alias}
        - i want to blacklist {noun}                 : Add {noun} to the blacklisted terms
        - i want to remove from the blacklist {noun} : Remove {noun} from the blacklisted terms
```'''
    await message.channel.send(msg)


async def bot_add_blacklist(message, content, command):
    if await check_permission(message):
        request = content.replace(command, '')

        if not add_blacklist(request):
            await bot_send_error(message, f'Blacklist term `{request}` already exists!')
            return None

        await bot_send_message(message, f'`{request}` is now blacklisted!')


async def bot_delete_blacklist(message, content, command):
    if await check_permission(message):
        request = content.replace(command, '')

        if not delete_blacklist(request):
            await bot_send_error(message, f'Blacklist term `{request}` does not exist!')
            return None

        await bot_send_message(message, f'`{request}` is no longer blacklisted!')


async def bot_search(message, content, command):
    if content not in blacklist:
        if message.channel.is_nsfw():

            request = content.replace(command, '')
            request = '_'.join(request.split(' ')[::-1])

            msg = await message.channel.send(f'Caching results for `{request}`')
            posts = search(request)
            await msg.delete()

            if len(posts) > 0:
                try:
                    if posts[1] == 429:
                        await bot_send_message(message, posts[0])
                        return None
                except:
                    pass

                data = get_image(posts['posts'])
                if data is not None:
                    try:
                        if data[1] == 429:
                            await bot_send_message(message, data[0])
                            return None
                    except:
                        pass

                    file = discord.File(data['file'], path.split(data['filename'])[-1])
                    await message.channel.send(f'<@!{message.author.id}> here you go: ', file=file)

                    data['file'].close()
                    unlink(data['filename'])

            else:
                await message.channel.send(f'Can\'t find any results for `{request}`, sorry <@!{message.author.id}>')
                return None

        else:
            await bot_send_error(message, 'This channel is not marked as NSFW!')
            return None

    else:
        await bot_send_error(message, 'This search term is blacklisted!')
        return None


