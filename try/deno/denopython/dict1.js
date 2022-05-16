import { python } from "https://deno.land/x/python/mod.ts";

const dict = python.dict({ prop: "value" });
console.log('dict=', dict)
console.log('dict.prop.valueOf()=', dict.prop.valueOf());
console.log('dict.prop=', dict.prop);
console.log('dict.prop = "new value"')
dict.prop = "new value";
console.log('dict.prop.valueOf()=', dict.prop.valueOf());
console.log('dict.prop=', dict.prop);
console.log('"prop" in dict=', "prop" in dict);
console.log('"prop2" in dict=', "prop2" in dict);
