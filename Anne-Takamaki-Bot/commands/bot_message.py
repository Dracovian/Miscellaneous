from .bot_configuration import safeids


botmessages = []


async def bot_send_message(message, content):
    botmessages.append(await message.channel.send(content))


async def bot_send_error(message, content):
    await bot_send_message(message, f'> {message.content} - <@!{message.author.id}>')
    await bot_send_message(message, content)


async def unpermitted(message):
    await bot_send_error(message, 'You are not permitted to use this command.')


async def check_permission(message):
    if message.author.id in safeids:
        return True

    await unpermitted(message)
    return False
