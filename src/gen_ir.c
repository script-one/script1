#include <gen0.c>
#include <stdint.h>

#define ir_t int

ir_t code[NMAX], *cp = code, *lcp = code;
ir_t data[NMAX], *dp = data;
typedef struct {
    Map
} env_t;

#define eir(c) { *cp++=c; }

static void dump_ir() {
    while (lcp < cp) {
        ir_t ir = *lcp++;
        char ir_name[20];
        if (ir >= End) emit("error\n");
        key_name(ir, ir_name);
        emit("%s", ir_name);
        if (ir >= Lea && ir <= Adj)
            emit(" %d", *lcp++);
    }
    emit("\n");
}

static void gen_num(node_t *node) {
    eir(Imm);
    int value;
    sscanf(node->ptk->str, "%d", &value);
    eir(value);
    gen_token(node);
}

static void gen_id(node_t *node) {
    char id[100];
    copy_str(node->ptk->str, node->ptk->len, id);
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
    if (n->type == Global) {
        emit("@");
    } else if (n->type == This) {
        emit("$");
    }
    gen_code(n->array[0]);
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
        emit("=");
        gen_code(exp);
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
