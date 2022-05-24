#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define debug(...) { if (dbg) printf(__VA_ARGS__); }
#define NMAX 100000
#define error(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define size(x) (sizeof(x)/sizeof(typeof (x)))
#define contain(set, ch) strchr(set, ch)
#define ok(exp) { if (!(exp)) error("ok() fail at file=%s, line=%d\n", __FILE__, __LINE__); }
#define fail() { error("Fail: not implemented yet!"); ok(0); }
// lex
enum { // token : 0-127 直接用該字母表達， 128 以後用代號。
  None=0,
  Or='|',And='&', Xor='^',Add='+',Sub='-',Mul='*',Div='/', Mod='%',
  AsciiEnd=128, 
  Id=130, Num, Str, Array, Function, 
  Pair, Block, Args, Params, Param, 
  ForIn, ForOf, ForTo, Stmts, Stmt, 
  Expr, Item, Term, Assign, Type, 
  Token, Pid, Key, Lambda, ClassBody,
  KeyBegin=199, 
  Import, As, If, While, For, 
  Else, In, Of, To, Step, 
  Await, New, Continue, Break, Return, 
  Fn, Class, Map, Try, Catch, Throw,
  KeyEnd,
  Op1Begin, Neg, Inc, Dec, Global, This, Op1End, 
  Op2Begin, Lor, Land, Eq, Neq, Le, Ge, Shl, Shr, Op2End,
  End,
};

typedef struct token_t {
    int tk;     // token 型態
    int line;   // 所在行號
    char *str;  // token 的字串
    int len;    // token 的字串長度
} token_t;

// ast
typedef struct node_t node_t;
typedef struct array_t array_t;
typedef struct link_t link_t;
typedef struct list_t list_t;

struct node_t {
  int type;
  int len;
  token_t *ptk;
  union {
    list_t  *list;
    node_t  *node;
    node_t  **array;
  };
};

struct link_t {
  node_t *node;
  link_t *next;
};

struct list_t {
  // int len;
  link_t *head;
};

char *ifile, *ofile;
FILE *ofp;
int src, dbg, o_run, o_dump;
char *source;

// API
char* key_name(int key, char *name);
int read_source(char *file);
bool head_eq(char *str1, int len1, char *str2);
bool tail_eq( char *str, char *end);
char back_skip(char *end, char *set);
void lex(char *source);
node_t *parse(char *source);
void gen_s1(node_t *root);
void gen_js(node_t *root);
void gen_dart(node_t *root);
void gen_py(node_t *root);

// void gen_c(node_t *root);
