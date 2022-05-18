int inc(x) { return x+1; }

double add(x,y) { return x+y; }

void main() {
    print('inc(2)='+inc(2).toString());
    print('add(2,3)=${add(2.0,3.0)}');
}
