#include <s1.h>
#include <lib.c>
#include <ir.c>
#include <env.c>
#include <obj.c>

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

int run() {
  printf("==================run================\n");
  env_init();
  ir_t *p = code;
  obj_t *a = NULL;
  bool is_stop = false;
  while (1) {
    if (p >= cp) error("no more code...\n");
    ir_t op = *p++;
    char opname[20];
    op_name(op, opname);
    printf("%s ", opname);
    char *s; int n; double f; obj_t *o;
    if (op == Float) {
      f = (double) *p++;
      printf(" %lf", f);
    } else if (op == Str) {
      s = (char*) *p++;
      printf(" '%s'", s);
    } else if (op == Get || op == Var || op == Fn || op == Src) {
      s = (char*) *p++;
      printf(" %s", s);
    } else if (op == Narg || op == Ent || op == Jmp || op == Bz || op == Bnz || op == Adj) {
      n = *p++;
      printf(" %d", n);
    }
    printf("\n");
    switch (op) {
      case Fn:
        env_pushf(s); // 新增函數堆疊，將參數加入其中
        break;
      case Param:
        break;
      case Ent:
        env_params_end();
        break;
      case Lev: case Ret: 
        env_popf();
        break;
      case Var:
        a = env_push_var(s);
        break;
      case Get:
        a = env_get_var(s);
        break;
      case Local:
        a = env_get_local(n);
        break;
      case Str:
        a = env_get_str(s); 
        break;
      case Float:
        a = env_get_float(f);
        break;
      case Call:
        p = *--sp;
        break;
      case Narg: // do nothing...
        break;
      case Jmp:
        p = p + n;
        break;
      case Bz:
        if (obj_iszero(a)) p = p + n;
        break;
      case Bnz:
        if (!obj_iszero(a)) p = p + n;
        break;
      case Store:
        obj_assign(*--sp, a);
        break;
      case Push:
        *sp++ = a;
        break;
      case Print:
        obj_print(a);
        break;
      case Exit:
        is_stop = true;
        break;
      case Lor:
        a = obj_lor(*--sp, a);
        break;
      case Land:
        a = obj_land(*--sp, a);
        break;
      case '!':
        a = obj_lnot(a);
        break;
      case Eq:
        a = obj_eq(*--sp, a);
        break;
      case Neq:
        a = obj_neq(*--sp, a);
        break;
      case Le:
        a = obj_le(*--sp, a);
        break;
      case Ge:
        a = obj_ge(*--sp, a);
        break;
      case Shl:
        a = obj_shl(*--sp, a);
        break;
      case Shr:
        a = obj_shr(*--sp, a);
        break;
      case Neg:
        a = obj_neg(a);
        break;
      case '+':
        a = obj_add(*--sp, a);
        break;
      case '-':
        a = obj_sub(*--sp, a);
        break;
      case '*':
        a = obj_mul(*--sp, a);
        break;
      case '/':
        a = obj_div(*--sp, a);
        break;
      case '%':
        a = obj_mod(*--sp, a);
        break;
      case '&':
        a = obj_band(*--sp, a);
        break;
      case '|':
        a = obj_bor(*--sp, a);
        break;
      case '^':
        a = obj_bxor(*--sp, a);
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
