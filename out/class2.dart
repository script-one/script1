// source file: prog/class2.s1
import '../sys/s1.dart';

class Person {
    var name;
    var age;
                                                   // (5) 
    Person([name,age])                             // (5) 
    {                                              // (5) 
        this.name=name;                            // (6) 
        this.age=age;                              // (7) 
    }
                                                   // (9) 
    toString()                                     // (9) 
    {                                              // (9) 
        return (this.name+(' '+str(this.age)));    // (10) 
    }
}                                                  // (1) 
dynamic main()                                     // (14) 
{                                                  // (14) 
    log(Person);                                   // (15) 
    dynamic p=new Person('ccc',52);                // (17) 
    log(str(p));                                   // (18) 
    log(p);                                        // (19) 
}                                                  // (14) 

