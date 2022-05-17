import './s1.dart';

void main() {
    log('hello');
    log('hello', 'ccc');
    log('hello', 'ccc', '!');
    log('hello', 'ccc', '!', 32, []);
    var map = {'a':1, 'b':2, 'c':[3,4]};
    log(keys(map));
    log(values(map));
    log(range(1,10));
    log(range(1,10,2));
}
