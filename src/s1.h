#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

#define debug(...) { if (dbg) printf(__VA_ARGS__); }
#define NMAX 100000
#define error(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define size(x) (sizeof(x)/sizeof(typeof(x[0])))
#define contain(set, ch) strchr(set, ch)
#define ok(exp) { if (!(exp)) error("ok() fail at file=%s, line=%d\n", __FILE__, __LINE__); }
#define fail() { error("Fail: not implemented yet!"); ok(0); }
#define max(a,b) (((a)>(b))?(a):(b))

extern char stab[], *stp;

#define st_printf(...) ({ char *stp0=stp; sprintf(stp, __VA_ARGS__); stp+=strlen(stp)+1; stp0; })
#define st_add(str, len) st_printf("%.*s", (int)(len), (str))
#define st_token(ptk) st_add((ptk)->str, (ptk)->len)

enum {
  None = 0,
  AsciiEnd = 128, 
  TkBegin = 130, // lex:tk
    Id, Num, Str, 
  TkEnd,
  NodeTypeBegin = 140, // node:type
    Array, Function, Pair, Block, Args, 
    Params, Param, ForIn, ForOf, ForTo, 
    Stmts, Stmt, Expr, Item, Term, 
    Assign, Type, Token, Pid, Key, 
    Lambda, ClassBody, CExpr, 
  NodeTypeEnd,
  KeyBegin = 170, // node:type
    Import, As, If, While, For, 
    Else, In, Continue, Break, Return, 
    Fn, Class, Extends, Map, Try, 
    Catch, Throw, Async, Await, New,
  KeyEnd,
  Op1Begin = 200, 
    Neg, Inc, Dec, Global, This, 
  Op1End, 
  Op2Begin = 210, 
    Lor, Land, Eq, Neq, Le, Ge, Shl, Shr, 
  Op2End, 
  VmOpBegin = 220, 
    Get, Local, Var, Float, Src, 
    Arg, Ent, Jmp, Bz ,
    Bnz, Adj, Call, Ret, Lev, 
    Store, Push, /*Print, Exit,Narg, */ 
  VmOpEnd,
  End,
};

typedef struct k2i {
  char *k;
  int  i;
} k2i_t;

typedef struct token {
    int tk;     // token 型態
    int line;   // 所在行號
    char *str;  // token 的字串
    int len;    // token 的字串長度
} token_t;

// ast

typedef struct node {
  int type;
  int len;
  struct token *ptk;
  union {
    struct list *list;
    struct node *node;
    struct node **array;
  };
} node_t;

typedef struct link {
  struct node *node;
  struct link *next;
} link_t;

typedef struct list {
  struct link *head;
} list_t;

char *ifile, *ofile;
FILE *ofp;
int src, dbg, o_run, o_dump, o_lex, o_main;
char *source;

// API
char* key_name(int key, char *name);
int read_source(char *file);
bool head_eq(char *str1, int len1, char *str2);
bool tail_eq( char *str, char *end);
void copy_str(char *str, int len, char *to_str);
int k2i(k2i_t *table, int from, int to, char *k, int klen);
char *i2k(k2i_t *table, int from, int to, int i);
char back_skip(char *end, char *set);
void lex(char *source);
node_t *parse(char *source);
void gen_s1(node_t *root);
void gen_js(node_t *root);
void gen_dart(node_t *root);
void gen_py(node_t *root);
void gen_ir(node_t *root);
