#include <gen0.c>

static bool show_line = true;

static void line(int i) {
  if (show_line) {
    if (i>0) {
      int len = 50-(int)(ep-ebuf);
      emit("%*s", max(len, 0), "");
      emit(" %s (%d) \n", TailComment, i);
    }
    else { emit("\n"); };
    ep = ebuf;
  }
}

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

#ifndef __PYTHON__
// should emit semicolon
static bool semicolon() {
    char *p = ep-1;
    while (p > ebuf && strchr("\t ", *p)) p--;
    // return !(p==ebuf || strchr("};", *p));
    return !(p==ebuf || strchr(";", *p));
}
#endif

// stmt
static void gen_stmt(node_t *stmt) {
    if (top == 0 || peek() == Block) {
        indent(block_level);
    } else {
        emit(" ");
    }
    gen_code(stmt->node);
#ifndef __PYTHON__
    if (semicolon()) emit(";");
#endif
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

/*
// block = { stmts }
static void gen_block(node_t *block) {
    line(block->ptk->line); // emit("\n");
    #ifndef __PYTHON__
        indent(block_level-1); emit(BlockBegin); line(block->ptk->line);
    #endif
    gen_stmts(block->node); // stmts
    #ifndef __PYTHON__
        indent(block_level-1); emit(BlockEnd);
    #endif
}
*/
// ------------- moved from gen_j.c to here -------------------
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
