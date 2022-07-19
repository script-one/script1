#include <math.h>

#define i32(f) (int32_t)floor(f)

// The Lisp object type
enum {
    // Regular objects visible from the user
    TNONE = 0, // 未定義
    // TINT,      // 整數
    TFLOAT,    // 雙精度浮點數
    TSTRING,   // 字串
    TARRAY,    // 陣列
    // TLIST,     // 串列
    // TSYMBOL,   // 符號
    // TPRIMITIVE,// 基本函數
    TFUNCTION, // 自訂函數
    // TENV       // 環境變數 frame
};

// typedef struct struct obj struct obj;
// typedef struct obj_link_t obj_link_t;
// typedef struct obj_func_t obj_func_t;

// The object type
struct obj {
    int type; // 物件型態
    int size; // 大小 (a->size or string length ...)
    union {
        // int64_t i;   // 程式位址
        double f;    // 浮點數值
        char   *str; // 字串常數
        // struct olink *list; // 物件串列
        struct obj** a;
        struct obj* (*func)(struct obj*); // 函數
    };
};

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
    if (a->type == TSTRING && o->type == TSTRING) {
        o->str = st_printf("%s%s", a->str, o->str);
    }
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
    if (o == NULL) {
        printf("(obj:null)");
        return NULL;
    }
    switch (o->type) {
        case TNONE:
            printf("(obj:none)");
            break;
        case TFLOAT:
            printf("%lf", o->f);
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

struct obj *o_log(struct obj *args) {
    for (int i=0; i<args->size; i++) {
        o_print(args->a[i]);
    }
    printf("\n");
    return NULL;
}

struct obj *o_call(struct obj *o, struct obj *arg) {
    ok(o->type == TFUNCTION);
    return o->func(arg);
}
