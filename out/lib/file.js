// source file: prog/lib/file.s1

export async function copyText(file1,file2)        // (1) 
{                                                  // (1) 
    let text1=await readText(file1);               // (2) 
    await writeText(file2,text1);                  // (3) 
}                                                  // (1) 

