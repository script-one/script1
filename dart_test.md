# dart_test

```dart
$ ./dart_test.sh
++ ./dart_run.sh hello
// source file: prog/hello.s1
void main() {
var name='script1';                                // (1) 
print(('hello '+name));                            // (2) 
}
hello script1
++ ./dart_run.sh array
// source file: prog/array.s1
void main() {
num mean(a) {                                      // (1)
  var s=0.0;                                       // (2)
  for (var x in a) s=(s+x);                        // (3)
;                                                  // (3)
  return (s/a.length);                             // (4)
}                                                  // (1)
print('mean([1 2 3 4 5])=${mean([1.0,2,3,4,5])}'); // (7)
}
mean([1 2 3 4 5])=3.0
++ ./dart_run.sh fn_t
// source file: prog/fn_t.s1

int inc(x) {                                       // (1)
  return (x+1);                                    // (1)
}                                                  // (1)
double add(x,y) {                                  // (3)
  return (x+y);                                    // (3)
}                                                  // (3)
void main() {                                      // (5)
  print('inc(2)=${inc(2)}');                       // (6)
  print('add(2.0,3.0)=${add(2.0,3.0)}');           // (7)
}                                                  // (5)

inc(2)=3
add(2.0,3.0)=5.0
++ ./dart_run.sh if_t
// source file: prog/if_t.s1
void main() {
num max(x,y) {                                     // (1)
  if (x>y) return x;                               // (1)
 else return y;                                    // (1)
;                                                  // (1)
}                                                  // (1)
print('max(3 5)=${max(3,5)}');                     // (3)
}
max(3 5)=5
```
