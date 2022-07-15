#define NVAR 10000
#define NFUNC 100

struct func {
    char *fname;
    int param_start;
    int fp;
    // int local_start;
};

char *vars[NVAR];
int var_top;
struct func fstack[NFUNC];
int f_top;

void env_init() {
    var_top = 0;
    f_top = 0;
}

int env_pushvar(char *vname) {
    vars[var_top] = vname;
    return var_top++;
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
    var_top = f->param_start;
    return f;
}

void env_params_end() {
    env_peekf()->fp = env_pushvar("");
    // f->local_start = f->fp+1;
}

int env_findlocal(char *vname) {
    struct func *f = env_peekf();
    for (int i=f->param_start; i<var_top; i++) {
        if (strcmp(vname, vars[i])==0) {
            return i-f->fp;
        }
    }
    return 0;
}
