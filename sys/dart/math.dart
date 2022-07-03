import "dart:math" as math;

var PI = math.pi;
var E  = math.e;
var sin = math.sin;
var cos = math.cos;
var tan = math.tan;
var asin= math.asin;
var acos= math.acos;
var atan= math.atan;
var exp = math.exp;
var sqrt= math.sqrt;
var pow = math.pow;
var ln = math.log;

var _R = math.Random();

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
