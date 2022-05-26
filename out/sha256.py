# source file: prog/sha256.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

import * as H from 'https://deno.land/std/hash/mod.ts'; # (1) 
def hash(text):                                    # (3) 
  h1=H.createHash('sha256');                       # (4) 
  h1.update(text);                                 # (5) 
  return str(h1);                                  # (6) 
                                                   # (3) 
record={'nonce':0,'data':'john => mary $2.7'}      # (9) 
json=JSON.stringify(record,null,2);                # (14) 
log('json=',json);                                 # (15) 
digest=hash(json);                                 # (17) 
log('digest=',digest);                             # (18) 

