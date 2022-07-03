import 'dart:convert';
import 'package:crypto/crypto.dart';

String hash(String text, [String method="sha256"]) {
    List<int> bytes = utf8.encode(text);
    return sha256.convert(bytes).toString();
}
