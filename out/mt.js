// source file: prog/mt.s1
import '../sys/s1.js'

let e2c={dog:`狗`,cat:`貓`,a:`一隻`,the:`這隻`,chase:`追`,bite:`吃`} // (1) 
function translate(ewords){                        // (3) 
  let cwords=[];                                   // (4) 
  for (let e of ewords)   {                        // (5) 
    cwords=push(cwords,e2c[e]);                    // (6) 
}                                                  // (5) 
                                                   // (5) 
  return cwords;                                   // (8) 
}                                                  // (3) 
let c=translate([`a`,`dog`,`chase`,`a`,`cat`]);    // (11) 
log(c);                                            // (12) 
if (typeof main == 'function') main()
