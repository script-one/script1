import 'dart:convert';

dynamic toJson(o) {
    return jsonEncode(o);
}

dynamic fromJson(str) {
    return jsonDecode(str);
}
