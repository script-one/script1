// source file: prog/import.s1
import '../sys/s1.js'

import * as H from 'https://deno.land/std/hash/mod.ts'; // (1) 
function hash(text){                               // (3) 
  let h1=H.createHash('sha256');                   // (4) 
  h1.update(text);                                 // (5) 
  return str(h1);                                  // (6) 
}                                                  // (3) 
log('hash(hello)=',hash('hello'));                 // (9) 
if (typeof main == 'function') main()
