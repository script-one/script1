// source file: prog/obj.s1
import '../sys/s1.js'

let ccc={name:`ccc`,age:52,str:function () {       // (4) 
  return (`name=`+(this.name+(` age=`+this.age))); // (5) 
}}                                                 // (1) 
log(ccc.str());                                    // (9) 
if (typeof main == 'function') main()
