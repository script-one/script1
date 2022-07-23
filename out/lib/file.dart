// source file: prog/lib/file.s1
import 'package:script1/script1.dart';

dynamic copyText([file1,file2]) async              // (1) 
{                                                  // (1) 
    dynamic text1=await readText(file1);           // (2) 
    await writeText(file2,text1);                  // (3) 
}                                                  // (1) 

