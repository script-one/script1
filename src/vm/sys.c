obj_t *sys_log(obj_t *args) {
    for (int i=0; i<args->size; i++) {
        o_print(args->a[i]);
    }
    printf("\n");
    return NULL;
}

obj_t *sys_exit(obj_t *args) {
    exit(0);
    return NULL;
}

// system function range(from, to, step)
// 這裡牽涉到 generator/yield 的議題，要仔細考慮如何處理才下手
// https://www.sobyte.net/post/2022-05/deep-learn-generators/ 
// 以上這篇有詳細介紹 js 的 yield 實作方法
typedef struct range {
    double from, to, step, v;
} range_t;

obj_t *range_next(obj_t *o) {
    range_t *r = (range_t*) o->iter->data;
    double nv = r->v+r->step;
    if (nv > r->to) return NULL;
    r->v = nv;
    return o;
}

#define clone(o) ({ void *p=calloc(sizeof(o), 1); memcpy(p, &o, sizeof(o)); p; })

obj_t *sys_range(obj_t *args) {
    ok(args->size >= 2);
    double from = (int) args->a[0]->f;
    double to = (int) args->a[1]->f;
    double step = (args->size>=3)?(int) args->a[2]->f:1.0;

    obj_t *o = env_new_obj(TITERATOR);
    range_t r = {.from=from, .to=to, .step=step, .v=0 };
    void *data = clone(r);
    iterator_t iter = { .data=data, .next=range_next };
    o->iter = clone(iter);
    return o;
}
