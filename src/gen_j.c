#include <gen1.c>

static void gen_cexpr(node_t *e1, node_t *e2, node_t *e3) {
    gen_code(e1);
    emit("?");
    gen_code(e2);
    emit(":");
    gen_code(e3);
}

// if expr stmt (else stmt)?
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2) {
    emit("if "); gen_code(exp);
    gen_code(stmt1);
    if (stmt2) {
        emit(" else");
        gen_code(stmt2);
    }
}
