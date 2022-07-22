// source file: prog/class3.s1
import '../sys/s1.js'

class Vehicle {                                    // (4) 
    honk()                                         // (4) 
    {                                              // (4) 
        return '';                                 // (5) 
    }
}                                                  // (1) 
class Car extends Vehicle {                        // (11) 
    honk()                                         // (11) 
    {                                              // (11) 
        log('BAAAAA');                             // (12) 
    }
}                                                  // (9) 
class SportsCar extends Car {                      // (19) 
    constructor(brand){
	super();
    this.brand=brand; // (20) 
}
}                                                  // (16) 
export function main()                             // (24) 
{                                                  // (24) 
    let benzzz=new SportsCar('Benzzz');            // (25) 
    log(benzzz.brand);                             // (26) 
    benzzz.honk();                                 // (27) 
}                                                  // (24) 
if (typeof main == 'function') main()
