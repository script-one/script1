#include <obj.c>

#define NVAR 10000
#define NFUNC 100

struct func {
    char *fname;
    int frame_start;
    int frame_base;
    int frame_end;
};

struct var {
    char *name;
    struct obj *o;
};

struct var vars[NVAR];
int var_top;
struct func fstack[NFUNC];
int f_top;

void env_init() {
    var_top = 0;
    f_top = 0;
}

int env_pushvar(char *vname) {
    struct var *v = &vars[var_top];
    v->name = vname;
    v->o = o_new(TNONE);
    return var_top++;
}

struct func* env_pushf(char *fname) {
    struct func *f = &fstack[f_top++];
    f->fname = fname;
    f->frame_start = var_top;
    return f;
}

struct func* env_peekf() {
    struct func *f = &fstack[f_top];
    return f;
}

struct func* env_popf() {
    struct func *f = &fstack[--f_top];
    f->frame_end = var_top;
    var_top = f->frame_start;
    return f;
}

void env_params_end() {
    env_peekf()->frame_base = env_pushvar("");
}

int env_find_local(char *vname) {
    struct func *f = env_peekf();
    for (int i=f->frame_start; i<var_top; i++) {
        if (strcmp(vname, vars[i].name)==0) {
            return i-f->frame_base;
        }
    }
    return 0;
}

struct var *env_get_local(int i) {
    struct func *f = env_peekf();
    return &vars[f->frame_base+i];
}
