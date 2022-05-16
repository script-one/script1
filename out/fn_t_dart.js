// source file: prog/fn_t_dart.s1
import '../sys/s1.js'

function inc(x) {                                  // (1) 
  return (x+1);                                    // (1) 
}                                                  // (1) 
function add(x,y) {                                // (3) 
  return (x+y);                                    // (3) 
}                                                  // (3) 
function main() {                                  // (5) 
  print(`inc(2)=${inc(2)}`);                       // (6) 
  print(`add(2.0,3.0)=${add(2.0,3.0)}`);           // (7) 
}                                                  // (5) 
if (main) main()
