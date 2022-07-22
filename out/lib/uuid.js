// source file: prog/lib/uuid.s1

import * as R from 'random.js';                    // (1) 
export function randomChar(chars)                  // (3) 
{                                                  // (3) 
  let i=R.rInt(0,chars.length);                    // (4) 
  return chars[i];                                 // (5) 
}                                                  // (3) 
export function randomStr(chars,len)               // (8) 
{                                                  // (8) 
  let list=[];                                     // (9) 
  let clen=len(chars);                             // (10) 
  for (let i of range(0,len))                      // (11) 
  {                                                // (11) 
    let ci=R.rInt(0,clen);                         // (12) 
    push(list,chars[ci]);                          // (13) 
  };                                               // (11) 
                                                   // (11) 
  return join(list,'');                            // (15) 
}                                                  // (8) 
let BASE='0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'; // (18) 
export function baseChars(base)                    // (20) 
{                                                  // (20) 
  return substr(BASE,0,base);                      // (21) 
}                                                  // (20) 
export function randomBase(base,len)               // (24) 
{                                                  // (24) 
  return randomStr(baseChars(base),len);           // (25) 
}                                                  // (24) 
export function s4()                               // (28) 
{                                                  // (28) 
  return randomBase(16,4);                         // (29) 
}                                                  // (28) 
export function guid()                             // (33) 
{                                                  // (33) 
  return (s4()+(s4()+('-'+(s4()+('-'+(s4()+('-'+(s4()+('-'+(s4()+(s4()+s4()))))))))))); // (34) 
}                                                  // (33) 

