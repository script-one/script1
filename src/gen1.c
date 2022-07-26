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

static void gen_str(node_t *node) {
#ifdef __CPP__
    emit("\"%.*s\"", node->ptk->len-2, node->ptk->str+1);
#else
    emit("'%.*s'", node->ptk->len-2, node->ptk->str+1);
#endif
}

// return expr
static void gen_return(int op, node_t *exp) {
    emit("return ");
    gen_code(exp);
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

// stmt
static void gen_stmt(node_t *stmt) {
    if (peek() == Block) {
        indent(block_level);
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

// array = [ expr* ]
static void gen_array(link_t *head) {
    #ifdef __CPP__
        emit("{");
        gen_list(head, ",");
        emit("}");
    #else
        emit("[");
        gen_list(head, ",");
        emit("]");
    #endif
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

// params = param*; param=field=exp; field=id(:type?)?
static void gen_params(link_t *head) {
    emit("(");
#ifdef __DART__
    if (head != NULL) emit("[");
#endif
    for (link_t *p = head; p != NULL; p = p->next) {
        node_t *nparam = p->node;
        node_t *nfield = nparam->array[0];
        node_t *nexp = nparam->array[1];
        node_t *nid = nfield->array[0];
        #ifdef __CPP__
            node_t *ntype = nfield->array[1];
            gen_code(ntype);
            emit(" ");
        #endif
        gen_code(nid);
        if (nexp) {
            emit("=");
            gen_code(nexp);
        }
        if (p->next != NULL) emit(",");
    }
#ifdef __DART__
    if (head != NULL) emit("]");
#endif
    emit(")");
}
