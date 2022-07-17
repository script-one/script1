#include <s1.h>
#include <lib.c>
#include <ir.c>
#include <env.c>

void parse_ir(char *line, char *op, char *arg) {
  *op='\0'; *arg='\0';
  sscanf(line, "%s %s", op, arg);
  if (strcmp(op, "str")==0) {
    sscanf(line, "%s '%[^']", op, arg);
  }
}

int asm2ir(char *line) {
  char p1[101], p2[101];
  printf("%s", line);
  parse_ir(line, p1, p2);
  ir_t op = op_code(p1);
  if (op < 0 || op==Src) return -1;
  eir(op);
  char *s=NULL; int n; double f;
  if (op == Float) {
    sscanf(p2, "%lf", &f);
    printf("=> %s %lf\n", p1, f);
    eir(s);
  } else if (op == Str || op == Get || op == Var || op == Fn) {
    s = st_printf("%s", p2);
    printf("=> %s %s\n", p1, s);
    eir(s);
  } else if (op == Narg || op == Ent || op == Jmp || op == Bz || op == Bnz || op == Adj) {
    n = atoi(p2);
    printf("=> %s %d\n", p1, n);
    eir(n);
  } else {
    printf("=> %s\n", p1);
  }
  return 0;
}

struct obj stack[NMAX];

int run() {
  printf("==================run================\n");
  env_init();
  ir_t *pc = code;
  struct obj *a = NULL, *sp = stack;
  bool is_stop = false;
  while (1) {
    if (pc >= cp) error("no more code...\n");
    ir_t op = *pc++;
    char opname[20];
    op_name(op, opname);
    printf("%s ", opname);
    char *s; int n; double f; // struct obj *o;
    if (op == Float) {
      f = (double) *pc++;
      printf(" %lf", f);
    } else if (op == Str) {
      s = (char*) *pc++;
      printf(" '%s'", s);
    } else if (op == Get || op == Var || op == Fn || op == Src) {
      s = (char*) *pc++;
      printf(" %s", s);
    } else if (op == Local || op == Narg || op == Ent || op == Jmp || op == Bz || op == Bnz || op == Adj) {
      n = *pc++;
      printf(" %d", n);
    }
    printf("\n");

    switch (op) {
      case Fn:
        env_pushf(s); // 新增函數堆疊，將參數加入其中
        break;
      case Param: case Var:
        n = env_pushvar(s);
        a = vars[n].o;
        break;
      case Ent:
        env_params_end();
        break;
      case Lev: case Ret: 
        env_popf();
        break;
      case Get:
        // a = env_get_var(s);
        break;
      case Local:
        a = env_get_local(n)->o;
        break;
      case Store:
        o_assign(--sp, a);
        break;
      case Push:
        o_assign(sp++, a);
        break;
      case Str:
        // a = env_get_str(s); 
        break;
      case Float:
        // a = env_get_float(f);
        break;
      case Call:
        // pc = call(a);
        break;
      case Narg: // do nothing...
        break;
      case Jmp:
        pc = pc + n;
        break;
      case Bz:
        if (o_iszero(a)) pc = pc + n;
        break;
      case Bnz:
        if (!o_iszero(a)) pc = pc + n;
        break;
      case Print:
        o_print(a);
        break;
      case Exit:
        is_stop = true;
        break;
      case Lor:
        o_lor(--sp, a);
        break;
      case Land:
        o_land(--sp, a);
        break;
      case '!':
        o_lnot(a);
        break;
      case Eq:
        o_eq(--sp, a);
        break;
      case Neq:
        o_neq(--sp, a);
        break;
      case Le:
        o_le(--sp, a);
        break;
      case Ge:
        o_ge(--sp, a);
        break;
      case Shl:
        o_shl(--sp, a);
        break;
      case Shr:
        o_shr(--sp, a);
        break;
      case Neg:
        o_neg(a);
        break;
      case '+':
        o_add(--sp, a);
        break;
      case '-':
        o_sub(--sp, a);
        break;
      case '*':
        o_mul(--sp, a);
        break;
      case '/':
        o_div(--sp, a);
        break;
      case '%':
        o_mod(--sp, a);
        break;
      case '&':
        o_band(--sp, a);
        break;
      case '|':
        o_bor(--sp, a);
        break;
      case '^':
        o_bxor(--sp, a);
        break;
      case '<':
        o_lt(--sp, a);
        break;
      case '>':
        o_gt(--sp, a);
        break;
      // case Adj:
      //   break;
      // case Src:
      //   break;
      default:
        break;
    }
    if (is_stop) break;
  }
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) error("%s <ir_file>\n", argv[0]);
  char *ifile = argv[1];

  FILE *f = fopen(ifile, "r");
  while (!feof(f)) {
    char line[256];
    fgets(line, sizeof(line), f);
    asm2ir(line);
  }
  fclose(f);

  run();
}
