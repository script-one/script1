Iterable<double> range(double from, double to, [double step=1.0]) sync* {
    for (var x=from; x<to; x+=step) {
        yield x;
    }
}

void main()
{
    var a = [9,8,7,6,5,4,3,2,1,0];
    for (var i in range(0,10)) {
        print(i);
        print(a[i.toInt()]);
    }
}