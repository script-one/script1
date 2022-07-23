// source file: prog/python.s1
import '../sys/s1.js'

import * as p from 'https://deno.land/x/python/mod.ts'; // (1) 
let python=p.python;                               // (3) 
let np=python['import']('numpy');                  // (4) 
let xpoints=np.array([1,8]);                       // (6) 
let ypoints=np.array([3,10]);                      // (7) 
log('xpoints=',xpoints);                           // (9) 
log('ypoints=',ypoints);                           // (10) 
let plt=python['import']('matplotlib.pyplot');     // (12) 
plt.plot(xpoints,ypoints);                         // (13) 
plt.show();                                        // (14) 
if (typeof main == 'function') main()
