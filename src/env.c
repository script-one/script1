#define NVAR 10000
#define NFUNC 100

struct func {
    char *fname;
    int param_start;
    int local_start;
};

char *vars[NVAR];
int var_top;
struct func fstack[NFUNC];
int f_top;

void env_init() {
    var_top = 0;
    f_top = 0;
}

void env_pushvar(char *vname) {
    vars[var_top++] = vname;
}

struct func* env_pushf(char *fname) {
    struct func *f = &fstack[f_top++];
    f->fname = fname;
    f->param_start = var_top;
    return f;
}

struct func* env_peekf() {
    struct func *f = &fstack[f_top];
    return f;
}

struct func* env_popf() {
    struct func *f = &fstack[--f_top];
    var_top = f->local_start;
    return f;
}
