// source file: prog/array.s1
void main() {
double mean(List<double> a) {                                      // (1) 
  double s=0.0;                                       // (2) 
  for (double i in a) s=s+i;                      // (3) 
  return (s/a.length);                             // (4) 
}                                                  // (1) 
print('mean([1 2 3 4 5])=${mean([1.0,2.0,3.0,4.0,5.0])}'); // (7) 
}
