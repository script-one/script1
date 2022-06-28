// source file: prog/_math.s1
import '../sys/s1.js'

log('sin(PI/4)=',sin((PI/4)));                     // (1) 
log('random()=',random());                         // (2) 
log('ln(E)=',ln(E));                               // (3) 
if (typeof main == 'function') main()
