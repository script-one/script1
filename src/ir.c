#include <s1.h>

#define word_t int64_t
// #define emit(...) {}

word_t code[NMAX], *cp = code, *lcp = code;
word_t data[NMAX], *dp = data;
char stab[NMAX], *stp = stab;

#define st_printf(...) ({ char *stp0=stp; sprintf(stp, __VA_ARGS__); stp+=strlen(stp)+1; stp0; })
#define st_add(str, len) st_printf("%.*s", (int)(len), (str))
#define st_token(ptk) st_add((ptk)->str, (ptk)->len)
#define eir(c) { *cp=(word_t) (c); cp++; }

static k2i_t ops[] = {
 // {"lea", Lea},
 // {"imm", Imm},
 {"load", Load},
 {"var", Var},
 {"str", Str},
 {"float", Float},
 {"//", Src},
 // {"def", Def},
 {"fn", Fn},
 {"narg", Narg},
 {"ent", Ent},
 {"jmp", Jmp},
 {"bz",  Bz},
 {"bnz", Bnz},
 {"adj", Adj},
 {"call", Call},
 {"lev", Lev}, 
 {"ssto", Ssto},
 {"push", Push},
 {"print", Print},
 {"exit", Exit},
 {"||", Lor},
 {"&&", Land},
 {"==", Eq},
 {"!=", Neq},
 {"<=", Le},
 {">=", Ge},
 {"<<", Shl},
 {">>", Shr},
 {"neg", Neg},
 {"+", '+'},
 {"-", '-'},
 {"*", '*'},
 {"/", '/'},
 {"%", '%'},
 {"&", '&'},
 {"|", '|'},
 {"!", '!'},
};

static char* op_name(int key, char *name) {
  if (key < AsciiEnd)
    sprintf(name, "%c", (char) key);
  else {
    char *k = i2k(ops, 0, size(ops), key);
    if (k) sprintf(name, "%s", k); else error("key_name(%d) not found ...", key);
  }
  return name;
}

static int op_code(char *name) {
  return k2i(ops, 0, size(ops), name, strlen(name));
}

