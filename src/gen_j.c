#include <gen1.c>

// block = { stmts }
static void gen_block(node_t *block) {
    line(block->ptk->line); // emit("\n");
    indent(block_level-1); emit(BlockBegin); line(block->ptk->line);
    gen_stmts(block->node); // stmts
    indent(block_level-1); emit(BlockEnd);
}

// while expr stmt
static void gen_while(node_t *exp, node_t *stmt) {
    emit("while "); 
    gen_code(exp);
    gen_code(stmt);
}

static void gen_str(node_t *node) {
    emit("'%.*s'", node->ptk->len-2, node->ptk->str+1);
}

static void gen_term(node_t *key, node_t *pid, link_t *head) {
    if (key) {
        gen_code(key);
        emit(" ");
    }
    gen_code(pid);
    for (link_t *p=head; p != NULL; p = p->next) {
        node_t *n = p->node; int op = n->type;
        if (op == '[') {
            emit("[");
            gen_code(n->array[0]);
            emit("]");
        } else if (op == '.') {
            emit(".");
            gen_code(n->array[0]);
        } else if (op == Args) {
            gen_code(n);
        }
    }
}

static void gen_map(node_t *nmap) {
    emit("{");
    link_t *head = nmap->list->head;
    gen_list(head, ",");
    emit("}");
}

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

static void gen_try(node_t *nbody, node_t *nexp, node_t *ncatch) {
    emit("try ");
    gen_code(nbody);
    emit(" catch (");
    gen_code(nexp);
    emit(")");
    gen_code(ncatch);
}
