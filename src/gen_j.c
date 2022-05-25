#include <gen1.c>

static void gen_cexpr(node_t *e1, node_t *e2, node_t *e3) {
    #ifdef __PYTHON__
    gen_code(e2);
    emit(" if ");
    gen_code(e1);
    emit(" else ");
    gen_code(e3);
    #endif 
   
    #ifndef __PYTHON__
    gen_code(e1);
    emit("?");
    gen_code(e2);
    emit(":");
    gen_code(e3);
    #endif 
}

static void gen_try(node_t *nbody, node_t *nexp, node_t *ncatch) {
    emit("try ");
    gen_code(nbody);
    emit(" catch (");
    gen_code(nexp);
    emit(")");
    gen_code(ncatch);
}

// array = [ expr* ]
static void gen_array(link_t *head) {
    emit("[");
    gen_list(head, ",");
    emit("]");
}

static void gen_key(node_t *node) {
    node_t *nkey = node->array[0];
    emit("%.*s", nkey->ptk->len, nkey->ptk->str);
}

static void gen_pair(node_t *n1, node_t *n2) {
    gen_code(n1);
    emit(":");
    gen_code(n2);
}

