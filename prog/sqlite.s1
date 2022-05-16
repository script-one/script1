import 'https://deno.land/x/sqlite/mod.ts' as sqlite

// Open a database
db := new sqlite.DB('test.db')
db.query('CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)')

names := ['Peter Parker', 'Clark Kent', 'Bruce Wayne']

// Run a simple query
for name of names
  db.query('INSERT INTO people (name) VALUES (?)', [name])

// Print out data in table
for r of db.query('SELECT id, name FROM people')
  print(r[0], r[1])

// Close connection
db.close()
