// source file: prog/class.s1
import '../sys/s1.js'

class Person {

}                                                  // (1) 
log(Person);                                       // (11) 
let p=new Person(`ccc`,52);                        // (13) 
log(str(p));                                       // (14) 
log(p);                                            // (15) 
if (typeof main == 'function') main()
