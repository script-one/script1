#include "obj.c"

#define NOBJ 10000
#define NVAR 10000
#define NFUNC 100

typedef struct var {
    char *name;
    obj_t *o;
} var_t;

typedef struct func {
    char *fname;
    var_t *vptr;
    var_t *vstart;
    var_t *vbase;
    var_t *vend;
} func_t;

obj_t objs[NOBJ], *objp=objs;
var_t vars[NVAR], *varp = vars;
func_t fstack[NFUNC], *fp=fstack;
obj_t *ostack[NMAX], **sp=ostack;

obj_t* env_new_obj(int type) {
    obj_t *r = objp++;
    memset(r, 0, sizeof(obj_t));
    r->type = type;
    return r;
}

obj_t* env_new_array(int size) {
    obj_t *o = env_new_obj(TARRAY);
    o->a = calloc(size, sizeof(obj_t*));
    o->size = size;
    return o;
}

var_t* env_push_var(char *vname) {
    var_t *v = varp++;
    v->name = vname;
    v->o = NULL;
    return v;
}

func_t* env_pushf(char *fname) {
    func_t *f = fp++;
    f->fname = fname;
    f->vstart = varp;
    f->vptr = varp;
    return f;
}

func_t* env_peekf() {
    return fp-1;
}

func_t* env_popf() {
    func_t *f = --fp;
    f->vend = varp;
    varp = f->vstart;
    return f;
}

void env_params_end() {
    env_peekf()->vbase = varp;
}

var_t *env_find_local(char *vname) {
    func_t *f = env_peekf();
    for (var_t *v = f->vstart; v<f->vend; v++) {
        if (strcmp(vname, v->name)==0) {
            return v;
        }
    }
    return NULL;
}

var_t *env_get_var(char *name) {
    for (var_t *v=varp-1; v>=vars; v--) {
        if (strcmp(v->name, name)==0) {
            // printf("==> env_get_var: %s at %d\n", name, (int) (v-vars));
            return v;
        }
    }
    return NULL;
}

void env_sysf(char *fname, fcall_t fcall) {
    var_t *v;
    obj_t *o;
    v = env_push_var(fname);
    o = env_new_obj(TFUNCTION);
    v->o = o;
    v->o->fcall = fcall;
}

#include "sys.c"

void env_init() {
    varp = vars; memset(vars, 0, sizeof(vars));
    fp = fstack; memset(fstack, 0, sizeof(fstack));
    sp = ostack; memset(ostack, 0, sizeof(ostack));
    env_sysf("log", sys_log);
    env_sysf("exit", sys_exit);
    env_sysf("range", sys_range);
}
