import 'package:flutter/material.dart';
import './home_page.dart';

void main() {
  runApp(Directionality(
          textDirection: TextDirection.ltr,
          child: Center(child:HomePage()))
  );
}
