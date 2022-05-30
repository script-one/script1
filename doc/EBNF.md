# Script1 -- EBNF

```EBNF
prog = stmts

stmts = stmt*

block = { stmts }

stmt = block                     |
       import str as id          |
       function                  |
       class id { function* }    |
       while expr stmt           | 
       if expr stmt (else stmt)? |
       for id in expr stmt       |
       try stmt catch expr stmt  |
       throw expr                |
       (return|?) expr           |
       continue                  |
       break                     |
       assign

assign = term(:type)?= expr

params = (assign*)

type = [^=),]*

function = fn(:id)? id(params) block

lambda = fn (params) { expr }

expr = bexpr (? expr : expr)

bexpr = item (op2 expr)?

item = str | array | lambda | map | factor

factor = (!-~) factor | num | ( expr ) | term

term = (await|new)? pid ( [expr] | . id | args )*

pid = (@|$)? id

array = [ expr* ]

map = { (str:expr)* }

args  = ( expr* ','? )

num : integer | float
str : '...'
id  : [a-zA-Z_][a-zA-Z_0-9]*
```
