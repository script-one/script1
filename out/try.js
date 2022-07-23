// source file: prog/try.s1
import '../sys/s1.js'

try                                                // (1) 
{                                                  // (1) 
    throw error('Error');                          // (2) 
}                                                  // (1) 
 catch (e)                                         // (3) 
{                                                  // (3) 
    log(e);                                        // (4) 
}                                                  // (3) 
                                                   // (1) 
if (typeof main == 'function') main()
