#include <gen0.c>

static void gen_num(node_t *node) {
    gen_token(node);
}

static void gen_id(node_t *node) {
    gen_token(node);
}

static void gen_op0(int op) {
    char name[20];
    key_name(op, name);
    emit("%s", name);
}

static void gen_op1(int op, node_t *node) {
    char name[20];
    key_name(op, name);
    emit("%s ", name);
    gen_code(node);
}

static void gen_op2(node_t *node1, int op, node_t *node2) {
    emit("(");
    gen_code(node1);
    char name[20];
    key_name(op, name);
    emit("%s", name);
    gen_code(node2);
    emit(")");
}

// args = ( expr* )
static void gen_args(link_t *head) {
    emit("(");
    gen_list(head, ",");
    emit(")");
}

// while expr stmt
static void gen_while(node_t *exp, node_t *stmt) {
    emit("while "); gen_code(exp);
    gen_code(stmt);
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

// should emit semicolon
static bool semicolon() {
    char *p = ep-1;
    while (p > ebuf && strchr("\t ", *p)) p--;
    return !(p==ebuf || strchr("};", *p));
}

// stmt
static void gen_stmt(node_t *stmt) {
    if (top == 0 || peek() == Block) {
        indent(block_level);
    } else {
        emit(" ");
    }
    gen_code(stmt->node);
    if (semicolon()) emit(";");
    line(stmt->ptk->line);
}

// stmts = stmt*
static void gen_stmts(node_t *node) {
    link_t *p = node->list->head;
    while (p != NULL) {
        gen_code(p->node);
        p = p->next;
    }
}

// block = { stmts }
static void gen_block(node_t *block) {
    indent(block_level-1);
    emit(" {"); line(block->ptk->line);
    gen_stmts(block->node); // stmts
    indent(block_level-1); emit("}"); // line(0);
}
