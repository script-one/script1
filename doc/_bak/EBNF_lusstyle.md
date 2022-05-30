# Cajson -- EBNF

```EBNF
stmts ::= { stmt ';' }

block ::= { stmts }

stmt ::= block                   |
       while expr stmt           | 
       if expr stmt [else stmt]  |
       for id (in|of) expr stmt  |
       for id:=expr to expr step expr stmt |
       (return|?) expr           |
       continue                  |
       break                     |
       assign

assign ::= pid(:type)?= expr

pid ::= [@|$] id

expr ::= item {op2 expr}

item ::= str | function | array | map | ( expr ) | factor

factor ::= [!-~] (factor | Num | '(' expr ')' | term)

term ::= pid { [expr] | . id | args ) }

pid ::= [@|$] id

function ::= fn (params) block

array ::= '[' {expr} ']'

map ::= '{' {(id|str|num):expr)} '}'

pairlist ::= {(id|str|num):expr)}

params ::= { assignlist }

assignlist ::= assign {',' assign }

args ::= ( exprlist )

exprlist ::= expr {',' expr}

op2 ::= + | - | * | / | % | < | > | == | != | <= | >= | && | '||' | ^ | & | '|'
```
