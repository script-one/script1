List array(n, [value=null]) {
    // var a = new List(n)
    return List.filled(n, value);
}

String join(List list, String spliter) {
    return list.join(spliter);
}

List map(List a, dynamic Function(dynamic) f) {
    return a.map(f).toList();
}

List where(List a, bool Function(dynamic) f) {
    return a.where(f).toList();
}

List reduce(List a, dynamic Function(dynamic, dynamic) f, dynamic init) {
    return a.fold(init, f).toList();
}
