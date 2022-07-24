import 'dart:io';

void log(a, [b='', c='', d='', e='', f='', g='', h='']) {
  print('${a} ${b} ${c} ${d} ${e} ${f} ${g} ${h}');
}

String input(String message) {
  stdout.write(message);
  var r = stdin.readLineSync();
  return (r==null)?"":r;
}
