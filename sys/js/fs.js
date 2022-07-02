export function cwd() {
  return Deno.cwd()
}

export async function readText(fpath, options={}) {
  return await Deno.readTextFile(fpath)
}

export async function writeText(fpath, text, options={}) {
  return await Deno.writeTextFile(fpath, text)
}

/*
export async function dirList(fpath) {
    let list = []
    for await (const entry of Deno.readDir(fpath)) {
        list.push(entry)
    }
    return list
}
global.dirList = dirList
*/

global.cwd = cwd
global.readText = readText
global.writeText = writeText
