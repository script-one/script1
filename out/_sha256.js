// source file: prog/_sha256.s1
import '../sys/s1.js'

let record={'nonce':0,'data':'john => mary $2.7'}; // (1) 
let json=JSON.stringify(record,null,2);            // (6) 
log('json=',json);                                 // (7) 
let digest=hash(json,'sha256');                    // (9) 
log('digest=',digest);                             // (10) 
if (typeof main == 'function') main()
