import "dart:math" as m;
class math {
  static const PI = m.pi;
  static const E = m.e;
}

var sin = m.sin;
var cos = m.cos;
var tan = m.tan;
var asin= m.asin;
var acos= m.acos;
var atan= m.atan;
var exp = m.exp;
var sqrt= m.sqrt;
var pow = m.pow;
var ln = m.log;

var _R = m.Random();

double random() {
    return _R.nextDouble();
}

int floor(double x) {
    return x.floor();
}

int round(double x) {
    return x.round();
}

int ceil(double x) {
    return x.ceil();
}

num abs(num x) {
    return x.abs();
}
