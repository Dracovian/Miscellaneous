from commands import add_command, call_command, init
from commands.bot_functions import *
client = discord.Client()


@client.event
async def on_ready():
    await add_command('clear_cache', bot_clear_cache, True)
    await add_command('clear_messages', bot_clear_messages, True)

    await add_command('trust', bot_add_trust, True)
    await add_command('untrust', bot_delete_trust, True)

    await add_command('alias', bot_add_alias, True)
    await add_command('dealias', bot_delete_alias, True)

    await add_command('blacklist', bot_add_blacklist, True)
    await add_command('whitelist', bot_delete_blacklist, True)

    await add_command('search', bot_search, False)
    await add_command('list_aliases', bot_list_aliases, False)

    await add_command('help', bot_list_functions, False)
    await init()


@client.event
async def on_message(message):
    if not message.author.bot:
        content = message.content.lower()
        await message.delete()

        # Search for content by alias
        if content in aliases.keys():
            await call_command('search', message, 3, aliases[content], 'i want to see some ')

        # Search for content by name
        if content.startswith('i want to see some '):
            await call_command('search', message, 3, content, 'i want to see some ')

        # Clear scan content cache
        if content.startswith('i want to clear the cache for '):
            await call_command('clear_cache', message, 3, content, 'i want to clear the cache for ')

        # Delete bot messages in bulk
        if content == 'i want you to clean up':
            await call_command('clear_messages', message, 1)

        # Add a new user to the trusted list
        if content.startswith('i want to trust '):
            await call_command('trust', message, 3, content, 'i want to trust ')

        # Delete a user from the trusted list
        if content.startswith('i want to untrust '):
            await call_command('untrust', message, 3, content, 'i want to untrust ')

        # Add a new command alias
        if content.startswith('i want to alias '):
            await call_command('alias', message, 3, content, 'i want to alias ')

        # Delete an alias
        if content.startswith('i want to dealias '):
            await call_command('dealias', message, 3, content, 'i want to dealias ')

        # List registered aliases
        if content == 'i want to see the aliases':
            await call_command('list_aliases', message, 1)

        # Add a new blacklisted term
        if content.startswith('i want to blacklist '):
            await call_command('blacklist', message, 3, content, 'i want to blacklist ')

        # Delete a blacklisted term
        if content.startswith('i want to remove from the blacklist '):
            await call_command('whitelist', message, 3, content, 'i want to remove from the blacklist ')

        # Show the help text
        if content == 'i want some help':
            await call_command('help', message, 1)

if __name__ == '__main__':
    client.run('')
