// source file: prog/_random.s1
import '../sys/s1.js'

import * as R from './lib/random.js';              // (1) 
log('rUnif(5,10)=',R.rUnif(5,10));                 // (3) 
if (typeof main == 'function') main()
