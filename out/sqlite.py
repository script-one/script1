# source file: prog/sqlite.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

import * as sqlite from 'https://deno.land/x/sqlite/mod.ts'; # (1) 
db=new sqlite.DB('test.db');                       # (4) 
db.query('CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)'); # (5) 
names=['Peter Parker','Clark Kent','Bruce Wayne']; # (7) 
for name in names: db.query('INSERT INTO people (name) VALUES (?)',[name]); # (11) 
                                                   # (10) 
for r in db.query('SELECT id, name FROM people'): log(r[0],r[1]); # (15) 
                                                   # (14) 
db.close();                                        # (18) 

