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
