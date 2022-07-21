#include <s1.h>

// intptr_t 參考 https://stackoverflow.com/questions/1464174/size-t-vs-uintptr-t
//   https://stackoverflow.com/questions/35071200/what-is-the-use-of-intptr-t
// If you're storing a size, use size_t. If you're storing a pointer, use intptr_t. 
#define ir_t int64_t // 這樣才能相容 double 浮點數，因此不用 intptr_t

ir_t code[NMAX], *cp = code, *lcp = code;
ir_t data[NMAX], *dp = data;
char *ir_src[NMAX];

#define eir(c) ({ *cp=(ir_t) (c); ir_src[cp - code + 1]=ir_src[cp - code]; cp++; })

static k2i_t ops[] = {
 {"get", Get},
 // {"local", Local},
 {"var", Var},
 {"param", Param},
 {"str", Str},
 {"float", Float},
 {"//", Src},
 {"array", Array},
 {"fn", Fn},
 // {"narg", Narg},
 {"ent", Ent},
 {"jmp", Jmp},
 {"jz",  Jz},
 {"jnz", Jnz},
 // {"adj", Adj},
 {"arg", Arg},
 {"call", Call},
 {"ret", Ret},
 {"lev", Lev}, 
 {"store", Store},
 {"push", Push},
 // {"print", Print},
 // {"exit", Exit},
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

static void ir_init() {
  memset(ir_src, 0, sizeof(ir_src));
  ir_src[0] = source;
}

static bool ir_op1s(ir_t op) {
  return op == Str || op == Get || op == Var || op == Param || op == Fn;
}

static bool ir_op1d(ir_t op) {
  return op==Array || op == Call || op == Ent || op == Jmp || op == Jz || op == Jnz;
}

static bool ir_op1(ir_t op) {
  return ir_op1d(op) || ir_op1s(op) || op == Float;
}

static char* ir_name(int key, char *name) {
  if (key < AsciiEnd)
    sprintf(name, "%c", (char) key);
  else {
    char *k = i2k(ops, 0, size(ops), key);
    if (k) sprintf(name, "%s", k); else error("key_name(%d) not found ...", key);
  }
  return name;
}

static int ir_code(char *name) {
  if (strlen(name)==1 && name[0] < 128) return name[0];
  return k2i(ops, 0, size(ops), name, strlen(name));
}

