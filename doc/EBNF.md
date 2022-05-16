# Cajson -- EBNF

```EBNF
stmts = stmt*

block = { stmts }

stmt = block                     |
       fn id(params) block       |
       while expr stmt           | 
       if expr stmt (else stmt)? |
       for id (in|of) expr stmt  |
       for id=expr to expr step expr stmt |
       (return|?) expr               |
       continue                  |
       break                     |
       assign

assign = pid(:type)?= expr

expr = item (op2 expr)*

item = Str | array | map | ( expr ) | factor

factor = (!-~) (factor) | Num | (expr) | term

term = pid ( [expr] | . id | args )*
// term = (await|new) pid ( [expr] | . id | args )*

pid = (@|$)? id

function = fn (params) block

array = [ expr* ]

map = { ((id|Str|Num):expr)* }

params = (assign ','?)*

args  = ( expr* ','? )

num : integer | float
str : '...'
id  : [a-zA-Z_][a-zA-Z_0-9]*
```
