#include <obj.c>

#define NOBJ 10000
#define NVAR 10000
#define NFUNC 100

struct var {
    char *name;
    struct obj *o;
};

struct func {
    char *fname;
    struct var *vptr;
    struct var *vstart;
    struct var *vbase;
    struct var *vend;
};

struct obj objs[NOBJ], *objp=objs;
struct var vars[NVAR], *varp = vars;
struct func fstack[NFUNC], *fp=fstack;
struct obj *ostack[NMAX], **sp=ostack;

struct obj* env_new_obj(int type) {
    struct obj *r = objp++;
    memset(r, 0, sizeof(struct obj));
    r->type = type;
    return r;
}

struct var* env_push_var(char *vname) {
    struct var *v = varp++;
    v->name = vname;
    v->o = NULL;
    return v;
}

struct func* env_pushf(char *fname) {
    struct func *f = fp++;
    f->fname = fname;
    f->vstart = varp;
    f->vptr = varp;
    return f;
}

struct func* env_peekf() {
    return fp-1;
}

struct func* env_popf() {
    struct func *f = --fp;
    f->vend = varp;
    varp = f->vstart;
    return f;
}

void env_params_end() {
    env_peekf()->vbase = varp;
}

struct var *env_find_local(char *vname) {
    struct func *f = env_peekf();
    for (struct var *v = f->vstart; v<f->vend; v++) {
        if (strcmp(vname, v->name)==0) {
            return v;
        }
    }
    return NULL;
}

struct var *env_get_var(char *name) {
    for (struct var *v=varp-1; v>=vars; v--) {
        if (strcmp(v->name, name)==0) {
            printf("==> env_get_var: %s at %d\n", name, (int) (v-vars));
            return v;
        }
    }
    return NULL;
}

void env_init() {
    varp = vars; memset(vars, 0, sizeof(vars));
    fp = fstack; memset(fstack, 0, sizeof(fstack));
    sp = ostack; memset(ostack, 0, sizeof(ostack));
    struct var *v;
    struct obj *o;
    v = env_push_var("log"); o = env_new_obj(TFUNCTION); v->o = o; v->o->func = o_print;
    printf("v->o->func=%p o_print=%p\n", v->o->func, o_print);
}
