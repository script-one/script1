import * as p from 'https://deno.land/x/python/mod.ts'

let python = p.python

python.load = function (name) {
    try { 
        return python.import(name); 
    } catch (error) { return null; }
}

export { python }
