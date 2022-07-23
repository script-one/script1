
double float(String str) {
    return double.parse(str);
}

bool equal(obj1, obj2) {
    return obj1 == obj2;
}

bool isDefined(x) {
    return x == null;
}

bool isInstanceOf(obj, Type cls) {
    return obj.runtimeType == cls;
}

bool isTypeEqual(obj1, obj2) {
    return obj1.runtimeType == obj2.runtimeType;
}

