char *ifile=NULL, *ofile=NULL;
int src, debug, o_run, o_dump;
char *source;

char *key_names[] = {
  "keybegin", 
  "import", "as", "if", "while", "for", 
  "else", "in", "of", "to", "step",  
  "await", "new", "continue", "break", "return", 
  "fn", "class", "map", "try", "catch", "throw",
  "keyend", 
  "op1begin", "-", "++", "--", "global.", "this.", "op1end",
  "op2begin", "||", "&&", "==", "!=", "<=", ">=", "<<", ">>", "op2end"
  "end",
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
