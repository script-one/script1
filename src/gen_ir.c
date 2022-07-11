#include <gen0.c>
#include <stdint.h>

word_t code[NMAX], *cp = code, *lcp = code;
word_t data[NMAX], *dp = data;
char stab[NMAX], *stp = stab;

static char *st_add(char *str, int len) {
  char *start = stp;
  memcpy(stp, str, len);
  stp += len;
  *stp++ = '\0';
  return start;
}

#define eir(c) { *cp++=c; }

static void dump_ir() {
    while (lcp < cp) {
        word_t ir = *lcp++;
        char ir_name[20];
        if (ir >= End) emit("error\n");
        key_name(ir, ir_name);
        emit("%s", ir_name);
        if (ir >= Lea && ir <= Adj) {
            word_t arg = *lcp++;
            if (ir == Imm || ir == Var) {
                emit(" %s", (char*) arg);
            } else {
                emit(" %d", (int) arg);
            }
        }
        emit("\n");
    }
    emit("\n");
}

static void gen_num(node_t *node) {
    char *p = st_add(node->ptk->str, node->ptk->len);
    eir(Imm); eir((word_t)p); // imm value
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

// ccc
static void gen_op2(node_t *node1, int op, node_t *node2) {
    emit("(");
    gen_code(node1);
    eir(Push);
    char name[20];
    key_name(op, name);
    emit("%s", name);
    gen_code(node2);
    eir(op);
    emit(")");
}

// args = ( expr* )
static void gen_args(link_t *head) {
    emit("(");
    // gen_list(head, ",");
    int narg = 0;
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node);
        eir(Push);
        if (p->next != NULL) emit(",");
        narg++;
    }
    eir(Narg); eir(narg);
    emit(")");
}

// should emit semicolon
static bool semicolon() {
    char *p = ep-1;
    while (p > ebuf && strchr("\t ", *p)) p--;
    // return !(p==ebuf || strchr("};", *p));
    return !(p==ebuf || strchr(";", *p));
}

// stmt
static void gen_stmt(node_t *stmt) {
    emit("// "); // source as comment
    if (top == 0 || peek() == Block) {
        indent(block_level);
    } else {
        emit(" ");
    }
    gen_code(stmt->node);
    if (semicolon()) emit(";");
    line(stmt->ptk->line);
    dump_ir();
}

// stmts = stmt*
static void gen_stmts(node_t *node) {
    link_t *p = node->list->head;
    while (p != NULL) {
        gen_code(p->node);
        p = p->next;
    }
}
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
    emit("%.*s", node->ptk->len, node->ptk->str);
    char *p = st_add(node->ptk->str, node->ptk->len);
    eir(Imm); eir((word_t)p);
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
        } else if (op == Args) { // function call
            eir(Push);
            gen_code(n);
            eir(Jsr);
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


static void gen_class(node_t *nid, node_t *eid, node_t *nbody) {
    emit("class ");
    gen_code(nid);

    if (eid) {
        emit(" extends ")
        gen_code(eid);
    }

    emit(" {"); block_level++;
    line(0);
    gen_list(nbody->list->head, "\n");
    line(0);
    block_level --; indent(block_level); emit("}");
}

static void gen_import(node_t *str1, node_t *id2) {
    emit("import ");
    gen_code(str1);
    emit(" as ");
    gen_code(id2);
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    node_t *nid = n->array[0];
    char name[100] = "";
    if (n->type == Global) {
        emit("@");
        sprintf(name, "@%.*s", nid->ptk->len, nid->ptk->str);
    } else if (n->type == This) {
        emit("$");
        sprintf(name, "$%.*s", nid->ptk->len, nid->ptk->str);
    } else {
        sprintf(name, "%.*s", nid->ptk->len, nid->ptk->str);
    }
    gen_code(nid);

    char *p = st_add(name, strlen(name));
    eir(Var); eir((word_t)p); // var id
}

// assign = pid(:type?)?= expr
static void gen_assign(node_t *pid, node_t *type, node_t *exp) {
    gen_code(pid);
    if (type) {
        emit(":");
        if (type->list != NULL)
            gen_list(type->list->head, "");
    }
    if (exp) {
        eir(Push);
        emit("=");
        gen_code(exp);
        eir(Store);
    }
}

// (return|?) expr
static void gen_return(int op, node_t *exp) {
    char name[20];
    key_name(op, name);
    emit("%s ", name);
    gen_code(exp);
}

// params = assign*
static void gen_params(link_t *head) {
    emit("(");
    gen_list(head, ",");
    emit(")");
}

// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    emit("for ");
    gen_code(id);
    emit(" in ");
    gen_code(exp);
    gen_code(stmt);
}

// function = fn(:id)? id(params) block
static void gen_function(int type, node_t *async, node_t *id, node_t *ret, node_t *params, node_t *block) {
    indent(block_level); 
    if (async) emit("async ");
    emit("fn");
    if (ret) { emit(":"); gen_code(ret); }
    emit(" ");
    if (id) gen_code(id);
    gen_code(params);
    gen_code(block);
}

void gen_ir(node_t *root) {
    emit("// source file: %s\n", ifile);
    line(0);
    gen_code(root);
    emit("\n");
}
