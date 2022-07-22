# source file: prog/lib/file.s1
import sys
import os
sys.path.append('sys')
from s1 import *

async def copyText(file1,file2):                   # (1) 
    text1=await readText(file1)                    # (2) 
    await writeText(file2,text1)                   # (3) 
                                                   # (1) 

