import asyncio
import aiofiles

# fs -- https://www.twilio.com/blog/working-with-files-asynchronously-in-python-using-aiofiles-and-asyncio
async def readText(fpath):
    async with aiofiles.open(fpath, mode='r') as f:
        text = await f.read()
        return text

async def writeText(fpath, text):
    async with aiofiles.open(fpath, mode='w') as f:
        await f.write(text)

async def main():
    text = await readText('async.md')
    await asyncio.sleep(1)
    await writeText('async2.md', text)

asyncio.run(main())
