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
    int size; // 物件大小
    union { // Object values.
        int    i;  // 整數值
        double f;  // 浮點數值
        char   *str;    // 字串常數
        // var_t  *var;   // 變數
        struct olink *list; // 物件串列
        struct obj* (*func)(struct obj*); // 函數
        /*
        // Primitive *fn; // 基本函數
        struct { // 一般函數
            struct struct obj *params; // 函數參數
            // struct struct obj *body;   // 函數 body
            ir_t *entry;
            struct struct obj *env;    // 環境變數
        };
        struct { // 環境變數
            struct struct obj *vars;
            struct struct obj *up;
        };
        // Forwarding pointer
        // void *moved; // 移動後物件的新位址
        */
    };
};

struct olink {
  struct obj *obj;
  struct olink *next;
};

#define OMAX 10000
struct obj objs[OMAX];
int o_top = 0; 

int o_idx(struct obj *o) {
    return o-objs;
}

struct obj *o_new(int type) {
    struct obj *r = &objs[o_top++];
    r->type = type;
    return r;
}

struct obj *o_add(struct obj *a, struct obj *b) {
    struct obj *r = &objs[o_top++];
    if (a->type == TFLOAT && b->type == TFLOAT ) {
        r->f = a->f+b->f;
    }
    return r;
}

struct obj *o_mul(struct obj *a, struct obj *b) {
    struct obj *r = &objs[o_top++];
    if (a->type == TFLOAT && b->type == TFLOAT ) {
        r->f = a->f*b->f;
    }
    return r;
}

struct obj *o_print(struct obj *a) {
    printf("obj=");
    switch (a->type) {
        case TFLOAT:
            printf("%lf", a->f);
            break;
        case TSTRING:
            printf("%s", a->str);
            break;
        case TLIST:
            for (struct olink *p = a->list; p!=NULL; p=p->next) {
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
