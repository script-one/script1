import asyncio
import aiofiles
import inspect
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

def f():
    return 3

print('inspect.iscoroutinefunction(main)='+str(inspect.iscoroutinefunction(main)))
print('inspect.iscoroutinefunction(f)='+str(inspect.iscoroutinefunction(f)))
print('xxx in globals()='+str('xxx' in globals()))
print('main in globals()='+str('main' in globals()))
print('xxx in vars()='+str('xxx' in vars()))
print('main in vars()='+str('main' in vars()))


# asyncio.run(main())
