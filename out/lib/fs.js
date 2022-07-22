// source file: prog/lib/fs.s1

export async function copy(file1,file2)            // (1) 
{                                                  // (1) 
  let text1=await read(file1);                     // (2) 
  await write(file2,text1);                        // (3) 
}                                                  // (1) 

