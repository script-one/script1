export 'dart/base.dart';
export 'dart/type.dart';
export 'dart/str.dart';
export 'dart/array.dart';
export 'dart/datetime.dart';
export 'dart/math.dart';
export 'dart/console.dart';
export 'dart/json.dart';
export 'dart/fs.dart';
export 'dart/regexp.dart';

/*
import 'dart:io';
import 'dart:math';

Map global = new Map();

void log(a, [b='', c='', d='', e='', f='', g='', h='']) {
  print('${a} ${b} ${c} ${d} ${e} ${f} ${g} ${h}');
}

String str(o) {
    return o.toString();
}

List keys(o) {
    return o.keys.toList();
}

List values(o) {
    return o.values.toList();
}

List<int> range(int from, int to, [int step=1]) {
    List<int> list=[];
    int i=from;
    while (i<to) {
        list.add(i);
        i+=step;
    }
    return list;
}

List push(List list, dynamic a) {
    list.add(a);
    return list;
}

int len(List list) {
    return list.length;
}

Exception error(String msg) {
    return Exception(msg);
}

List map(List a, dynamic Function(dynamic) f) {
    return a.map(f).toList();
}

Future<String> read(file) async {
    var f = File(file);
    var text = await (f.readAsString());
    return text;
}

Future<File> write(file, text) async {
    var f = File(file);
    return await (f.writeAsString(text));
}

var _R = Random();

double random() {
    return _R.nextDouble();
}
*/
