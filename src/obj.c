// The Lisp object type
enum {
    // Regular objects visible from the user
    TINT = 1,  // 整數
    TDOUBLE,   // 雙精度浮點數
    TSTRING,   // 字串
    TLIST,     // 串列
    TSYMBOL,   // 符號
    TPRIMITIVE,// 基本函數
    TFUNCTION, // 自訂函數
    TENV       // 環境變數 frame
};

typedef struct obj_t obj_t;
typedef struct obj_link_t obj_link_t;

// The object type
typedef struct obj_t {
    int type; // 物件型態
    int size; // 物件大小
    union { // Object values.
        int    ivalue;  // 整數值
        double dvalue;  // 浮點數值
        char   *str;    // 字串常數
        var_t  *var;   // 變數
        obj_link_t *list; // 物件串列
        // Primitive *fn; // 基本函數
        struct { // 一般函數
            struct obj_t *params; // 函數參數
            // struct obj_t *body;   // 函數 body
            word_t *entry;
            struct obj_t *env;    // 環境變數
        };
        struct { // 環境變數
            struct obj_t *vars;
            struct obj_t *up;
        };
        // Forwarding pointer
        // void *moved; // 移動後物件的新位址
    };
} obj_t;

struct obj_link_t {
  obj_t *obj;
  obj_link_t *next;
};

#define OMAX 10000
obj_t obj[OMAX];
int o_top = 0; 

obj_t *obj_new(int type) {
    obj_t *r = &obj[o_top++];
    r->type = type;
    return r;
}

obj_t *obj_add(obj_t *a, obj_t *b) {
    obj_t *r = &obj[o_top++];
    if (a->type == TDOUBLE && b->type == TDOUBLE ) {
        r->dvalue = a->dvalue+b->dvalue;
    }
    return r;
}

obj_t *obj_mul(obj_t *a, obj_t *b) {
    obj_t *r = &obj[o_top++];
    if (a->type == TDOUBLE && b->type == TDOUBLE ) {
        r->dvalue = a->dvalue*b->dvalue;
    }
    return r;
}

void obj_print(obj_t *a) {
    switch (a->type) {
        case TDOUBLE:
            printf("%lf", a->dvalue);
            break;
        case TSTRING:
            printf("%s", a->str);
            break;
        case TLIST:
            for (obj_link_t *p = a->list; p!=NULL; p=p->next) {
                obj_print(p->obj);
            }
            break;
        default:
            printf("(unknown type)");
    }
}
