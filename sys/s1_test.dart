import 'package:script1/script1.dart';

void g1() {
    glob['x'] = 5;
}

void main() {
    log('hello');
    log('hello', 'ccc');
    log('hello', 'ccc', '!');
    log('hello', 'ccc', '!', 32, []);
    var map = {'a':1, 'b':2, 'c':[3,4]};
    log(keys(map));
    log(values(map));
    log(list(range(1,10)));
    log(list(range(1,10,2)));
    glob['name'] = 'dart';
    log(glob);
    glob['x'] = 3;
    log('@x=', glob['x']);
    g1();
    log('@x=', glob['x']);
    // global.name = "dart in script1";
}
