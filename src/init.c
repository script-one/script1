char *ifile=NULL, *ofile=NULL;
int src=0, dbg=0, o_run=0, o_dump=0, o_lex = 0, o_main=0;
char *source;

char *key_names[] = {
  "keybegin", 
/*200*/ "import", "as", "if", "while", "for", 
/*205*/ "else", "in", "continue", "break", "return", 
/*210*/ "fn", "class", "extends", "__map__", "try", 
/*215*/ "catch", "throw", "async", "await", "new", 
/*220*/ "keyend", "op1begin", "-", "++", "--", 
/*225*/ "global.", "this.", "op1end","op2begin", 
/*230*/ "||", "&&", "==", "!=", "<=", ">=", 
/*235*/ "<<", ">>", "op2end", "vmOpBegin", "lea", 
/*240*/ "imm", "int", "double", "var", "cstr", "narg", "ent", "jmp", "bz", "bnz", "adj",
/*24..6*/ "jsr", "lev", "ld.i", "ld.c", 
/*250*/ "st.i", "st.b", "push","open", "read", 
/*255*/ "close", "print", "malc", "free", "mset", 
/*260*/ "mcmp", "exit", "VmOpEnd", "end",
};

int key_code(char *key, int len) {
  for (int i=KeyBegin+1; i<KeyEnd; i++) {
    int ni = i-KeyBegin;
    if (len == strlen(key_names[ni]) && memcmp(key, key_names[ni], len)==0)
      return i;
  }
  return -1;
}

char* key_name(int key, char *name) {
  if (key < AsciiEnd)
    sprintf(name, "%c", (char) key);
  else if (key > KeyBegin && key < End)
    sprintf(name, "%s", key_names[key-KeyBegin]);
  else
    error("key_name(%d) out of range...", key);
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
