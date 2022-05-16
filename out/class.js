// source file: prog/class.s1
import '../sys/s1.js'

class Person {                                     // (2) 
  constructor(name,age)   {                        // (2) 
    this.name=name;                                // (3) 
    this.age=age;                                  // (4) 
  }
                                                   // (6) 
  __str()   {                                      // (6) 
    return (this.name+(` `+this.age));             // (7) 
  }
}                                                  // (1) 
print(Person);                                     // (11) 
let p=new Person(`ccc`,52);                        // (13) 
print(str(p));                                     // (14) 
print(p);                                          // (15) 
if (typeof main == 'function') main()
