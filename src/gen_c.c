#include <gen1.c>

static void emit_str(char *str, int len) {
    emit("\"%.*s\"", len-2, str+1);
}

// array = [ expr* ]
static void gen_array(link_t *head) {
    emit("{");
    gen_list(head, ",");
    emit("}");
}

static void gen_str(node_t *node) {
    emit_str(node->ptk->str, node->ptk->len);
    // emit("\"%.*s\"", node->ptk->len-1, node->ptk->str+1);
    // gen_token(node);
}

static void gen_key(node_t *node) {
    fail();
    // node_t *nkey = node->array[0];
    // emit("%.*s", nkey->ptk->len, nkey->ptk->str);
}

static void gen_pair(node_t *n1, node_t *n2) {
    fail();
/*
    gen_code(n1);
    emit(":");
    gen_code(n2);
*/
}

// map = [ (expr:expr)* ]
static void gen_map(int type, link_t *head) {
    fail();
/*
    emit("{");
    gen_list(head, ",");
    emit("}");
*/
}


static void gen_import(node_t *str1, node_t *id2) {
    emit("#include ");
    emit_str(str1->ptk->str, str1->ptk->len);
/*
    emit("import * as ");
    gen_code(id2);
    emit(" from ");
    gen_code(str1);
*/
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    if (n->type == Global) {
        emit("global_");
    } else if (n->type == This) {
        emit("this_");
    }
    gen_code(n->array[0]);
}

// (await|new)? pid ( [expr] | . id | args )*
static void gen_term(node_t *key, node_t *pid, link_t *head) {
    if (key) {
        fail();
        // gen_code(key);
        // emit(" ");
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
    if (type) {
        gen_list(type->list->head, "");
        emit(" ");
    } 
    gen_code(pid);
    if (exp) {
        emit("=");
        gen_code(exp);
    }
}

// params = assign*
static void gen_params(link_t *head) {
    emit("(");
    for (link_t *p = head; p != NULL; p = p->next) {
        node_t **args = p->node->array;
        gen_assign(args[0], args[1], args[2]);
        if (p->next != NULL) emit(",");
    }
    emit(")");
    /*
    emit("(");
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node->array[0]); // id 
        if (p->next != NULL) emit(",");
    }
    emit(")");
    */
}

// (return|?) expr
static void gen_return(int op, node_t *exp) {
    emit("return ");
    gen_code(exp);
}

// for id op expr stmt
static void gen_for3(char *op, node_t *id, node_t *exp, node_t *stmt) {
    emit("type? t=");
    gen_code(exp);
    emit("for (int _i=0; _i<t.len; _i++) {");
    if (strcmp(op, "in")) { emit("=i;\n"); } else emit("=t[i];");
    gen_code(stmt);
    emit("}");
}

// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    gen_for3("in", id, exp, stmt);
}

// for id of expr stmt
static void gen_for_of(node_t *id, node_t *exp, node_t *stmt) {
    gen_for3("of", id, exp, stmt);
}

// for id=expr to expr (step expr) stmt
static void gen_for_to(node_t *id, node_t *from, node_t *to, node_t *step, node_t *stmt) {
    emit("for (int "); gen_code(id); emit("="); gen_code(from); 
    emit(";"); gen_code(id); emit("<="); gen_code(to); 
    emit(";"); gen_code(id); emit("+="); 
    if (step) { gen_code(step); } else { emit("1"); } emit(")")
    gen_code(stmt);
/*
    emit("for (let ");
    gen_code(id);
    emit("=");
    gen_code(from);
    emit(";");
    gen_code(id);
    emit("<=");
    gen_code(to);
    emit(";")
    gen_code(id);
    if (step) {
        emit("+=");
        gen_code(step);
    } else {
        emit("++");
    }
    emit(")");
    gen_code(stmt);
*/
}

// function = fn id?(params) block
static void gen_function(node_t *id, node_t *params, node_t *block) {
    emit("int ");
    if (id) gen_code(id);
    gen_code(params);
    gen_code(block);
}

void gen_c(node_t *root) {
    emit("// source file: %s\n", ifile);
    emit("#include <s1.h>\n");
    gen_code(root);
    emit("\n");
}

