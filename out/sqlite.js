// source file: prog/sqlite.s1
import '../sys/s1.js'

import * as sqlite from 'https://deno.land/x/sqlite/mod.ts'; // (1) 
let db=new sqlite.DB(`test.db`);                   // (4) 
db.query(`CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)`); // (5) 
let names=[`Peter Parker`,`Clark Kent`,`Bruce Wayne`]; // (7) 
for (let name of names) db.query(`INSERT INTO people (name) VALUES (?)`,[name]); // (11) 
;                                                  // (10) 
for (let r of db.query(`SELECT id, name FROM people`)) print(r[0],r[1]); // (15) 
;                                                  // (14) 
db.close();                                        // (18) 
if (typeof main == 'function') main()
