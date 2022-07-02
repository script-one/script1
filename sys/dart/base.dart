import 'dart:io';

Map global = new Map();

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

int len(dynamic x) {
    return x.length;
}

Exception error(String msg) {
    return Exception(msg);
}
