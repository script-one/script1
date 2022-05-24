#include <gen_j.c>

static void gen_str(node_t *node) {
    gen_token(node);
}

static void gen_class(node_t *nid, node_t *nbody) {
    emit("class ");
    gen_code(nid);
    emit(" {");
    line(0);
    gen_list(nbody->list->head, "\n");
    // gen_map(nbody);
    line(0);
    emit("}");
}

// map = [ (expr:expr)* ]
static void gen_map(node_t *nmap) {
    link_t *head = nmap->list->head;
    emit("{");
    gen_list(head, ",");
    emit("}");
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

// term = (await|new)? pid ( [expr] | . id | args )*
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
static void gen_function(int type, node_t *id, node_t *ret, node_t *params, node_t *block) {
    emit("fn");
    if (ret) { emit(":"); gen_code(ret); }
    emit(" ");
    if (id) gen_code(id);
    gen_code(params);
    gen_code(block);
}

void gen_s1(node_t *root) {
    emit("// source file: %s\n", ifile);
    line(0);
    gen_code(root);
    emit("\n");
}
