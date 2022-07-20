#include <math.h>

#define i32(f) (int32_t)floor(f)

// The Lisp object type
enum {
    // Regular objects visible from the user
    TNONE = 0, // 未定義
    TFLOAT,    // 雙精度浮點數
    TSTRING,   // 字串
    TARRAY,    // 陣列
    TFUNCTION, // 自訂函數
};

typedef struct obj* (*func_t)(struct obj*); // 函數

// The object type
struct obj {
    int type; // 物件型態
    int size; // 大小 (a->size or string length ...)
    union {
        double f;    // 浮點數值
        char   *str; // 字串常數
        struct obj** a;
        func_t func; // 函數
    };
};

struct obj* env_new_obj(int type);

#define fop2(a, op, b) \
    if ((a)->type == TFLOAT && (b)->type == TFLOAT) { \
      struct obj *o = env_new_obj(TFLOAT); \
      o->f = (a)->f op (b)->f; \
      return o; \
    }

#define iop2(a, op, b) \
    if ((a)->type == TFLOAT && (b)->type == TFLOAT) { \
      struct obj *o = env_new_obj(TFLOAT); \
      o->f = i32((a)->f) op i32((b)->f); \
      return o; \
    }

#define fop1(op, a) \
    if ((a)->type == TFLOAT) { \
      struct obj *o = env_new_obj(TFLOAT); \
      o->f = op (a)->f; \
      return o; \
    }

#define iop1(op, a) \
    if ((a)->type == TFLOAT) { \
      struct obj *o = env_new_obj(TFLOAT); \
      o->f = op i32((a)->f); \
      return o; \
    }

bool o_iszero(struct obj *o) {
    return o->f == 0.0;
}

struct obj *o_neg(struct obj *a) {
    fop1(-, a);
    return NULL;
}

struct obj *o_not(struct obj *a) {
    fop1(!, a);
    return NULL;
}

struct obj *o_lnot(struct obj *a) {
    iop1(~, a);
    return NULL;
}

struct obj *o_lor(struct obj *a, struct obj *b) {
    iop2(a, ||, b);
    return NULL;
}

struct obj *o_land(struct obj *a, struct obj *b) {
    iop2(a, &&, b);
    return NULL;
}

struct obj *o_eq(struct obj *a, struct obj *b) {
    fop2(a, ==, b);
    return NULL;
}

struct obj *o_neq(struct obj *a, struct obj *b) {
    fop2(a, !=, b);
    return NULL;
}

struct obj *o_le(struct obj *a, struct obj *b) {
    fop2(a, <=, b);
    return NULL;
}

struct obj *o_ge(struct obj *a, struct obj *b) {
    fop2(a, >=, b);
    return NULL;
}

struct obj *o_lt(struct obj *a, struct obj *b) {
    fop2(a, <, b);
    return NULL;
}

struct obj *o_gt(struct obj *a, struct obj *b) {
    fop2(a, >, b);
    return NULL;
}

struct obj *o_add(struct obj *a, struct obj *b) {
    fop2(a, +, b);
    if (a->type == TSTRING && b->type == TSTRING) {
        struct obj *o = env_new_obj(TSTRING);
        o->str = st_printf("%s%s", a->str, b->str);
        return o;
    }
    return NULL;
}

struct obj *o_sub(struct obj *a, struct obj *b) {
    fop2(a, -, b);
    return NULL;
}

struct obj *o_mul(struct obj *a, struct obj *b) {
    fop2(a, *, b);
    return NULL;
}

struct obj *o_div(struct obj *a, struct obj *b) {
    fop2(a, /, b);
    return NULL;
}

struct obj *o_mod(struct obj *a, struct obj *b) {
    iop2(a, %, b);
    return NULL;
}

struct obj *o_band(struct obj *a, struct obj *b) {
    iop2(a, &, b);
    return NULL;
}

struct obj * o_bor(struct obj *a, struct obj *b) {
    iop2(a, |, b);
    return NULL;
}

struct obj *o_bxor(struct obj *a, struct obj *b) {
    iop2(a, ^, b);
    return NULL;
}

struct obj *o_shl(struct obj *a, struct obj *b) {
    iop2(a, <<, b);
    return NULL;
}

struct obj *o_shr(struct obj *a, struct obj *b) {
    iop2(a, >>, b);
    return NULL;
}

struct obj *o_print(struct obj *o) {
    if (o == NULL) {
        printf("(obj:null)");
        return NULL;
    }
    switch (o->type) {
        case TNONE:
            printf("(obj:none)");
            break;
        case TFLOAT:
            printf("%g", o->f);
            break;
        case TSTRING:
            printf("%s", o->str);
            break;
        case TARRAY:
            printf("[");
            for (int i=0; i<o->size; i++) {
                o_print(o->a[i]);
                if (i != o->size-1) printf(",");
            }
            printf("]");
            break;
        /*
        case TLIST:
            for (struct olink *p = o->list; p!=NULL; p=p->next) {
                o_print(p->obj);
            }
            break;
        */
        case TFUNCTION:
            printf("(function:%p)", o->func);
            break;
        default:
            printf("(unknown:type=%d)", o->type);
    }
    return NULL;
}

struct obj *o_call(struct obj *o, struct obj *arg) {
    ok(o->type == TFUNCTION);
    return o->func(arg);
}
