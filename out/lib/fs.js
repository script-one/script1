// source file: lib/fs.s1
import '../sys/s1.js'

async function copy(file1,file2)                   // (1) 
{                                                  // (1) 
  let text1=await read(file1);                     // (2) 
  await write(file2,text1);                        // (3) 
}                                                  // (1) 

