// source file: prog/try.s1
import '../sys/s1.js'

try  {                                             // (1) 
  throw Error(`Error`);                            // (2) 
}                                                  // (1) 
 catch (error) {                                   // (3) 
  print(error);                                    // (4) 
}                                                  // (3) 
;                                                  // (1) 
if (typeof main == 'function') main()
