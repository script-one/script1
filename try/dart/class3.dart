// source file: prog/class2.s1
// import '../sys/s1.dart';

class Person {
  var name;
  var age;
                                                   // (5) 
  Person(name,age)  {                              // (5) 
    this.name=name;                                // (6) 
    this.age=age;                                  // (7) 
  }  
                                                   // (9) 
  __str()  {                                       // (9) 
    // return (this.name+(' '+this.age.toString()));             // (10) 
    return '${this.name} ${this.age}';             // (10) 
  }  
}                                                  // (1) 


void main() {

print(Person);                                       // (14) 
var p=new Person('ccc',52);                        // (16) 
print(p.__str());                                            // (18) 
}
