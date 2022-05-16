import { python } from "https://deno.land/x/python/mod.ts";

const list = python.list([1, 2, 3]);
console.log('list=', list)
console.log('list[0].valueOf()=', list[0].valueOf());
console.log('list[0] = 42')
list[0] = 42;
console.log('list[0].valueOf()=', list[0].valueOf());
let i=0;
for (const v of list) {
    console.log(v.valueOf());
    i++;
}
