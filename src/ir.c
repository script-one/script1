static k2i_t ops[] = {
 {"lea", Lea},
 {"imm", Imm},
 {"var", Var},
 {"//", Src},
 {"def", Def},
 {"narg", Narg},
 {"ent", Ent},
 {"jmp", Jmp},
 {"bz",  Bz},
 {"bnz", Bnz},
 {"adj", Adj},
 {"var", Var},
 {"call", Call},
 {"lev", Lev}, 
 {"store", Store},
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
