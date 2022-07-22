// source file: prog/class3.s1
import '../sys/s1.dart';

class Vehicle {
    var brand;
                                                   // (4) 
    honk()                                         // (4) 
    {                                              // (4) 
        return '';                                 // (5) 
    }
}                                                  // (1) 
class Car extends Vehicle {
                                                   // (11) 
    honk()                                         // (11) 
    {                                              // (11) 
        log('BAAAAA');                             // (12) 
    }
}                                                  // (9) 
class SportsCar extends Car {
    var brand;
                                                   // (19) 
    SportsCar([brand])                             // (19) 
    {                                              // (19) 
        this.brand=brand;                          // (20) 
    }
}                                                  // (16) 
dynamic main()                                     // (24) 
{                                                  // (24) 
    dynamic benzzz=new SportsCar('Benzzz');        // (25) 
    log(benzzz.brand);                             // (26) 
    benzzz.honk();                                 // (27) 
}                                                  // (24) 

