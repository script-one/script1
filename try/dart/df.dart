import 'dart:math';

// var step = 0.001;
const step = 0.001;

dynamic df([f,x,h=step])
{
  dynamic dy=(f((x+h))-f(x));
  return (dy/h);
}

void main() {
  print('df(sin,PI/4)=${df(sin,pi/4)}');
}
