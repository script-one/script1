// source file: prog/_sqlite.s1
import '../sys/s1.js'

let db=new Sqlite('test.db');                      // (1) 
db.query('CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)'); // (2) 
let names=['Peter Parker','Clark Kent','Bruce Wayne']; // (4) 
for (let name of names) db.query('INSERT INTO people (name) VALUES (?)',[name]); // (7) 
                                                   // (6) 
for (let r of db.query('SELECT id, name FROM people')) log(r[0],r[1]); // (10) 
                                                   // (9) 
db.close();                                        // (12) 
if (typeof main == 'function') main()
