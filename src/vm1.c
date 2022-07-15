#include <s1.h>
#include <lib.c>
#include <ir.c>
#include <obj.c>

k2i_t syms[10000];
int sym_top = 0;

int sym_get(char *name) {
  int oi = k2i(syms, 0, sym_top, name, strlen(name));
  if (oi >= 0) return oi;
  return -1;
}

int sym_add(char *name) {
  int si = sym_get(name);
  if (si >= 0) return si;
  struct obj *o = o_new(TNONE);
  k2i_t *s = &syms[sym_top++];
  s->k=st_printf(name);
  s->i=o_idx(o);
  return s->i;
}

struct obj *obj_get(int oi) {
  return &objs[oi];
}

void sym_init() {
  int oi; struct obj *o;
  oi = sym_add("log"); o = obj_get(oi); o->type = TFUNCTION; o->func = o_print;
}

int asm2ir(char *line) {
  char p1[21], p2[101];
  sscanf(line, "%20s %100s", p1, p2);
  if (p1[0]=='\0' || head_eq(p1, 2, "//")) return -1;
  printf("%s", line);
  ir_t op = op_code(p1);
  if (op < 0) return -1;
  eir(op);
  // printf("%d ", (int) op);
  int oi, arg; 
  struct obj *o;
  switch (op) {
    case Fn:
      oi = sym_add(p2);
      printf("  fn %d\n", (int) oi);
      eir(oi);
      break;
    case Var:
      oi = sym_add(p2);
      printf("  var %d\n", (int) oi);
      eir(oi);
      break;
    case Load:
      oi = sym_get(p2);
      printf("p2=|%s| strlen(p2)=%d\n", p2, (int) strlen(p2));
      printf("  load %d\n", (int) oi);
      eir(oi);
      break;
    case Src:
      break;
    case Str: 
      ok(p2[0]=='\'');
      o = o_new(TSTRING);
      o->str = st_add(p2, strlen(p2));
      eir(o_idx(o));
      o_print(o);
      break;
    case Float:
      ok(isdigit(p2[0]));
      o = o_new(TFLOAT);
      o->f = atof(p2);
      eir(o->f);
      o_print(o);
      break;
    case Narg:
      arg = atoi(p2);
      eir(arg);
      break;
    default:
      break;
      // eir(op);
  }
  /*
  if (op == Str || op == Float || op == Load || op == Var || op == Fn || op == Src) {
    printf(" %s", p2);
  } else if (op == Narg || op == Ent || op == Jmp || op == Bz || op == Bnz || op == Adj ) {
    printf(" %s", p2);
  }
  printf("\n");
  */
  return 0;
}

int run() {
  printf("==================run================\n");
  ir_t *p = code;
  while (1) {
    if (p >= cp) error("no more code...\n");
    ir_t op = *p++, arg;
    char name[20];
    op_name(op, name);
    printf("%s ", name);
    switch (op) {
      case Fn:
      case Var:
      case Load:
      case Str:
      case Float:
      case Narg:
        arg = *p++;
        printf(" %d", (int) arg);
        break;
      case '+':
        break;
      case Push:
        break;
      case Ssto:
        break;
      case Call:
        break;
      case Exit:
        break;
      default: error("not handled yet!");
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
  if (argc < 2) error("%s <ir_file>\n", argv[0]);
  char *ifile = argv[1];

  sym_init();

  FILE *f = fopen(ifile, "r");
  while (!feof(f)) {
    char line[256];
    fgets(line, sizeof(line), f);
    asm2ir(line);
  }
  fclose(f);

  run();
}
