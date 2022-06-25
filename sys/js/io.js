export async function dirList(fpath) {
    let list = []
    for await (const entry of Deno.readDir(fpath)) {
        list.push(entry)
    }
    return list
}

export async function read(fpath, options={}) {
  return await Deno.readTextFile(fpath)
}

export async function write(fpath, text, options={}) {
  return await Deno.writeTextFile(fpath, text)
}

global.read = read
global.write = write
