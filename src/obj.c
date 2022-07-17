#include <math.h>

#define i32(f) (int32_t)floor(f)

// The Lisp object type
enum {
    // Regular objects visible from the user
    TNONE = 0, // 未定義
    TINT,      // 整數
    TFLOAT,   // 雙精度浮點數
    TSTRING,   // 字串
    TLIST,     // 串列
    TSYMBOL,   // 符號
    TPRIMITIVE,// 基本函數
    TFUNCTION, // 自訂函數
    TENV       // 環境變數 frame
};

// typedef struct struct obj struct obj;
// typedef struct obj_link_t obj_link_t;
// typedef struct obj_func_t obj_func_t;

// The object type
struct obj {
    int type; // 物件型態
    union {
        int64_t i;   // 程式位址
        double f;    // 浮點數值
        char   *str; // 字串常數
        struct olink *list; // 物件串列
        struct obj* (*func)(struct obj*); // 函數
    };
};

struct olink {
  struct obj *obj;
  struct olink *next;
};

#define OMAX 10000
struct obj objs[OMAX];
int o_top = 0;

#define fop2(a, op, o) \
    if ((a)->type == TFLOAT && (o)->type == TFLOAT) { \
      (o)->f = (a)->f op (o)->f; \
    }

#define iop2(a, op, o) \
    if ((a)->type == TFLOAT && (o)->type == TFLOAT) { \
      (o)->f = i32((a)->f) op i32((o)->f); \
    }

#define fop1(op, o) \
    if ((o)->type == TFLOAT) { \
      (o)->f = op (o)->f; \
    }

#define iop1(op, o) \
    if ((o)->type == TFLOAT) { \
      (o)->f = op i32((o)->f); \
    }

int o_idx(struct obj *o) {
    return o-objs;
}

struct obj *o_new(int type) {
    struct obj *r = &objs[o_top++];
    r->type = type;
    return r;
}

void o_assign(struct obj *o, struct obj *a) {
    o->type = a->type;
    o->f = a->f; // union 中的所有型態最大必須是 64bits，所以可以用 f (double) 指定之。
}

bool o_iszero(struct obj *o) {
    return o->f == 0.0;
}

void o_neg(struct obj *o) {
    fop1(-, o);
}

void o_not(struct obj *o) {
    fop1(!, o);
}

void o_lor(struct obj *a, struct obj *o) {
    fop2(a, ||, o);
}

void o_land(struct obj *a, struct obj *o) {
    fop2(a, &&, o);
}

void o_lnot(struct obj *o) {
    fop1(!, o);
}

void o_eq(struct obj *a, struct obj *o) {
    fop2(a, ==, o);
}

void o_neq(struct obj *a, struct obj *o) {
    fop2(a, !=, o);
}

void o_le(struct obj *a, struct obj *o) {
    fop2(a, <=, o);
}

void o_ge(struct obj *a, struct obj *o) {
    fop2(a, >=, o);
}

void o_lt(struct obj *a, struct obj *o) {
    fop2(a, <, o);
}

void o_gt(struct obj *a, struct obj *o) {
    fop2(a, >, o);
}

void o_add(struct obj *a, struct obj *o) {
    fop2(a, +, o);
}

void o_sub(struct obj *a, struct obj *o) {
    fop2(a, -, o);
}

void o_mul(struct obj *a, struct obj *o) {
    fop2(a, *, o);
}

void o_div(struct obj *a, struct obj *o) {
    fop2(a, /, o);
}

void o_mod(struct obj *a, struct obj *o) {
    iop2(a, %, o);
}

void o_band(struct obj *a, struct obj *o) {
    iop2(a, &, o);
}

void o_bor(struct obj *a, struct obj *o) {
    iop2(a, |, o);
}

void o_bxor(struct obj *a, struct obj *o) {
    iop2(a, ^, o);
}

void o_shl(struct obj *a, struct obj *o) {
    if ((a)->type == TFLOAT && (o)->type == TFLOAT) {
      (o)->f = i32((o)->f) << i32((a)->f);
    }
}

void o_shr(struct obj *a, struct obj *o) {
    if ((a)->type == TFLOAT && (o)->type == TFLOAT) {
      (o)->f = i32((o)->f) << i32((a)->f);
    }
}

struct obj *o_print(struct obj *o) {
    printf("obj=");
    switch (o->type) {
        case TFLOAT:
            printf("%lf", o->f);
            break;
        case TSTRING:
            printf("%s", o->str);
            break;
        case TLIST:
            for (struct olink *p = o->list; p!=NULL; p=p->next) {
                o_print(p->obj);
            }
            break;
        default:
            printf("(unknown type)");
    }
    printf("\n");
    return NULL;
}

struct obj *o_call(struct obj *o, struct obj *arg) {
    ok(o->type = TFUNCTION);
    return o->func(arg);
}
