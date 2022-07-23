import 'dart:io';

Directory cwd() {
    return Directory.current;
}

Future<String> readText(file) async {
    var f = File(file);
    var text = await (f.readAsString());
    return text;
}

Future<File> writeText(file, text) async {
    var f = File(file);
    return await (f.writeAsString(text));
}
