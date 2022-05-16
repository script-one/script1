// source file: prog/sha256.s1
import '../sys/s1.js'

import * as H from 'https://deno.land/std/hash/mod.ts' // (1) 
function hash(text) {                              // (3) 
  let h1=H.createHash('sha256')                    // (4) 
  h1.update(text)                                  // (5) 
  return str(h1)                                   // (6) 
}                                                  // (3) 
let record={nonce:0,data:'john => mary $2.7'}      // (9) 
let json=JSON.stringify(record,null,2)             // (14) 
print('json=',json)                                // (15) 
let digest=hash(json)                              // (17) 
print('digest=',digest)                            // (18) 

