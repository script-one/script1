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
    TITERATOR, // iterator，像是 range(0,len)
};

typedef struct obj obj_t;
typedef obj_t* (*fcall_t)(obj_t*); // 函數
typedef struct iterator iterator_t;

// The object type
struct obj {
    int type; // 物件型態
    int size; // 大小 (a->size or string length ...)
    union {
        double f;    // 浮點數值
        char   *str; // 字串常數
        obj_t **a;   // 陣列
        fcall_t fcall; // 函數
        iterator_t *iter; // iterator
    };
};

struct iterator {
    void *data;
    fcall_t next;
};

obj_t* env_new_obj(int type);

#define fop2(a, op, b) \
    if ((a)->type == TFLOAT && (b)->type == TFLOAT) { \
      obj_t *o = env_new_obj(TFLOAT); \
      o->f = (a)->f op (b)->f; \
      return o; \
    }

#define iop2(a, op, b) \
    if ((a)->type == TFLOAT && (b)->type == TFLOAT) { \
      obj_t *o = env_new_obj(TFLOAT); \
      o->f = i32((a)->f) op i32((b)->f); \
      return o; \
    }

#define fop1(op, a) \
    if ((a)->type == TFLOAT) { \
      obj_t *o = env_new_obj(TFLOAT); \
      o->f = op (a)->f; \
      return o; \
    }

#define iop1(op, a) \
    if ((a)->type == TFLOAT) { \
      obj_t *o = env_new_obj(TFLOAT); \
      o->f = op i32((a)->f); \
      return o; \
    }

bool o_iszero(obj_t *o) {
    if (o==NULL) return true;
    if (o->type == TNONE) return true;
    if (o->f == 0.0) return true;
    return false;
}

obj_t *o_neg(obj_t *a) {
    fop1(-, a);
    return NULL;
}

obj_t *o_not(obj_t *a) {
    fop1(!, a);
    return NULL;
}

obj_t *o_lnot(obj_t *a) {
    iop1(~, a);
    return NULL;
}

obj_t *o_lor(obj_t *a, obj_t *b) {
    iop2(a, ||, b);
    return NULL;
}

obj_t *o_land(obj_t *a, obj_t *b) {
    iop2(a, &&, b);
    return NULL;
}

obj_t *o_eq(obj_t *a, obj_t *b) {
    fop2(a, ==, b);
    return NULL;
}

obj_t *o_neq(obj_t *a, obj_t *b) {
    fop2(a, !=, b);
    return NULL;
}

obj_t *o_le(obj_t *a, obj_t *b) {
    fop2(a, <=, b);
    return NULL;
}

obj_t *o_ge(obj_t *a, obj_t *b) {
    fop2(a, >=, b);
    return NULL;
}

obj_t *o_lt(obj_t *a, obj_t *b) {
    fop2(a, <, b);
    return NULL;
}

obj_t *o_gt(obj_t *a, obj_t *b) {
    fop2(a, >, b);
    return NULL;
}

obj_t *o_add(obj_t *a, obj_t *b) {
    fop2(a, +, b);
    if (a->type == TSTRING && b->type == TSTRING) {
        obj_t *o = env_new_obj(TSTRING);
        o->str = st_printf("%s%s", a->str, b->str);
        return o;
    }
    return NULL;
}

obj_t *o_sub(obj_t *a, obj_t *b) {
    fop2(a, -, b);
    return NULL;
}

obj_t *o_mul(obj_t *a, obj_t *b) {
    fop2(a, *, b);
    return NULL;
}

obj_t *o_div(obj_t *a, obj_t *b) {
    fop2(a, /, b);
    return NULL;
}

obj_t *o_mod(obj_t *a, obj_t *b) {
    iop2(a, %, b);
    return NULL;
}

obj_t *o_band(obj_t *a, obj_t *b) {
    iop2(a, &, b);
    return NULL;
}

obj_t * o_bor(obj_t *a, obj_t *b) {
    iop2(a, |, b);
    return NULL;
}

obj_t *o_bxor(obj_t *a, obj_t *b) {
    iop2(a, ^, b);
    return NULL;
}

obj_t *o_shl(obj_t *a, obj_t *b) {
    iop2(a, <<, b);
    return NULL;
}

obj_t *o_shr(obj_t *a, obj_t *b) {
    iop2(a, >>, b);
    return NULL;
}

obj_t *o_print(obj_t *o) {
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
        case TFUNCTION:
            printf("(function:%p)", o->fcall);
            break;
        default:
            printf("(unknown:type=%d)", o->type);
    }
    return NULL;
}

obj_t *o_call(obj_t *o, obj_t *arg) {
    ok(o->type == TFUNCTION);
    return o->fcall(arg);
}
