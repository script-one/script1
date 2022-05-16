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
