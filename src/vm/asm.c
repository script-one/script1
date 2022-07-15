#include <map.h>
#include <unistd.h>

#define TMAX 10000

typedef struct {
    char *name;
    char type;
    int idx;
} var_t;

map_t sym_table;
var_t vars[TMAX];
int var_top = 0;

static void ir_init() {
  map_new(&sym_table, TMAX);
}

static void ir_close() {
  map_free(&sym_table);
}

static var_t* sym_add(char *name) {
  var_t *var = map_lookup(&sym_table, name);
  if (var) return var;
  
  char *vname = st_add(name, strlen(name));

  var = &vars[var_top];
  *var = (var_t) { .name=vname, .type='G', .idx=var_top++ };
  map_add(&sym_table, vname, var);
  // printf("map_add(%s)\n", vname);
  return var;
}

void sym_dump() {
  for (int i=0; i<var_top; i++) {
    var_t *var = &vars[i];
    printf("%s %c %d\n", var->name, var->type, var->idx);
  }
}
