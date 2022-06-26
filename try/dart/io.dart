import 'dart:io';
 
Future<String> read(file) async {
    var f = File(file);
    var text = await (f.readAsString());
    return text;
}

Future<File> write(file, text) async {
    var f = File(file);
    return await (f.writeAsString(text));
}

void main() async {
  var text = await read('hello.txt');
  print(text);
  await write('hello2.txt', text);
}