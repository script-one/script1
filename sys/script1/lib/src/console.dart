import 'dart:io';

void log(a, [b='', c='', d='', e='', f='', g='', h='']) {
  print('${a} ${b} ${c} ${d} ${e} ${f} ${g} ${h}');
}

String input(String message) {
  stdout.write(message);
  return stdin.readLineSync();
}
