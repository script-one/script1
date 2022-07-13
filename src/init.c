char *ifile=NULL, *ofile=NULL;
int src=0, dbg=0, o_run=0, o_dump=0, o_lex = 0, o_main=0;
char *source;

k2i_t keys[] = {
 {"import", Import},
 {"as", As},
 {"if", If},
 {"while", While},
 {"for", For},
 {"else", Else },
 {"in", In}, 
 {"continue", Continue},
 {"break", Break}, 
 {"return", Return}, 
 {"fn", Fn},
 {"class", Class},
 {"extends", Extends}, 
 {"try", Try},
 {"catch", Catch}, 
 {"throw", Throw},
 {"async", Async},
 {"await", Await},
 {"new", New}, 
 {"||", Lor},
 {"&&", Land},
 {"==", Eq},
 {"!=", Neq},
 {"<=", Le},
 {">=", Ge},
 {"<<", Shl},
 {">>", Shr},
 {"global.", Global},
 {"this.", This},
 {"-", Neg},
}; 

char* key_name(int key, char *name) {
  if (key < AsciiEnd)
    sprintf(name, "%c", (char) key);
  else {
    char *k = i2k(keys, 0, size(keys), key);
    if (k) sprintf(name, "%s", k); else error("key_name(%d) not found ...", key);
  }
  return name;
}

bool is_op1(int op) {
  return contain("!~@$", op) || (op > Op1Begin && op <Op1End) || op == Return;
}

bool is_op2(int op) {
  return contain("+-*/%&|^<>", op) || (op > Op2Begin && op <Op2End);
}

int read_source(char *file) {
  FILE *fd;
  if (!(fd = fopen(file, "r"))) {
    printf("could not open(%s)\n", file);
    return -1;
  }
  int len = fread(source, 1, sizeof(source), fd);
  source[len++] = '\n'; source[len++] = '\0';
  // printf("=====source=======\n%s\n==================\n", source);
  return 0;
}
