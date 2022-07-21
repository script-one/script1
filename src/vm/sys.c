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

obj_t *sys_range(obj_t *args) {
    ok(args->size >= 2);
    // int from = (int) args->a[0]->f;
    // int to = (int) args->a[1]->f;
    // int step = (args->size>=3)?(int) args->a[2]->f:1;
    obj_t *r = env_new_obj(TITERATOR);
    // ...
    return r;
}
