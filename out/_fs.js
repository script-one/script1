// source file: prog/_fs.s1
import '../sys/s1.js'

let text=await readText('./data/test.json');       // (1) 
log(text);                                         // (2) 
let obj=fromJson(text);                            // (3) 
log(obj);                                          // (4) 
let text2=toJson(obj);                             // (5) 
await writeText('./data/test2.json',text2);        // (7) 
if (typeof main == 'function') main()
