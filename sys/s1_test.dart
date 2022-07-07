import './s1.dart';

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
    global['name'] = 'dart';
    log(global);
    // global.name = "dart in script1";
}
