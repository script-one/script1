# dart_test

```js
$ ./dart_test.sh
++ ./js_run.sh hello
// source file: prog/hello.s1
import '../sys/s1.js'

let name=`script1`;                                // (1) 
print((`hello `+name));                            // (2) 
if (typeof main == 'function') main()
hello script1
++ ./js_run.sh array
// source file: prog/array.s1
import '../sys/s1.js'

function mean(a) {                                 // (1)
  let s=0.0;                                       // (2)
  for (let x of a) s=(s+x);                        // (3)
;                                                  // (3)
  return (s/a.length);                             // (4)
}                                                  // (1)
print(`mean([1 2 3 4 5])=${mean([1.0,2,3,4,5])}`); // (7)
if (typeof main == 'function') main()
mean([1 2 3 4 5])=3
++ ./js_run.sh fn_t
// source file: prog/fn_t.s1
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
if (typeof main == 'function') main()
inc(2)=3
add(2.0,3.0)=5
++ ./js_run.sh if_t
// source file: prog/if_t.s1
import '../sys/s1.js'

function max(x,y) {                                // (1)
  if (x>y) return x;                               // (1)
 else return y;                                    // (1)
;                                                  // (1)
}                                                  // (1)
print(`max(3 5)=${max(3,5)}`);                     // (3)
if (typeof main == 'function') main()
max(3 5)=5
```
