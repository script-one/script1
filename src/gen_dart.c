#include <gen_j.c>

// class = 'class' id classBody
static void gen_class(node_t *nid, node_t *nbody) {
    emit("class ");
    gen_code(nid);
    emit(" {"); /*line(0);*/ block_level++;
    for (link_t *p = nbody->list->head; p != NULL; p = p->next) {
        ok(p->node->type == Function); // Function = op4(type, nid, nret, p1, b1);
        node_t *nid  = p->node->array[0];
        node_t *nret = p->node->array[1];
        node_t *nparams = p->node->array[2];
        node_t *nbody= p->node->array[3];

        char *name = nid->ptk->str; int len=nid->ptk->len;
        line(nid->ptk->line); indent(block_level); 
        if (head_eq(name, len, "__init")) {
            emit("constructor");
        } else {
            gen_code(nid);
        }
        // node_t *ntype = nval->array[1], *params = nval->array[2], *block=nval->array[3];
        // if (ntype) gen_code(ntype);
        if (nret) gen_code(nret);
        gen_code(nparams);
        gen_code(nbody);
        line(0);
    }
    block_level --;
    indent(block_level); emit("}");
}

static void gen_import(node_t *str1, node_t *id2) {
    emit("import * as ");
    gen_code(id2);
    emit(" from ");
    gen_code(str1);
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    if (n->type == Global) {
        emit("global['");
    } else if (n->type == This) {
        emit("this.");
    }
    gen_code(n->array[0]);
    if (n->type == Global) {
        emit("']");
    }
}

// assign = pid(:type?)?= expr
static void gen_assign(node_t *pid, node_t *type, node_t *exp) {
    if (type) emit("var ");
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
        gen_code(p->node->array[0]); // id 
        if (p->next != NULL) emit(",");
    }
    emit(")");
}

// (return|?) expr
static void gen_return(int op, node_t *exp) {
    emit("return ");
    gen_code(exp);
}

// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    emit("for (var ");
    gen_code(id);
    emit(" in ");
    gen_code(exp);
    emit(")");
    gen_code(stmt);
}

// function = fn(:id)? id?(params) block
static void gen_function(int type, node_t *id, node_t *ret, node_t *params, node_t *body) {
    if (type == Lambda) {
        gen_code(params);
        emit("=>");
        gen_code(body);
    } else {
        if (ret) { gen_code(ret); emit(" "); } else emit("void ");
        gen_code(id); // if (id) gen_code(id);
        gen_code(params);
        gen_code(body);
    }
}

void gen_dart(node_t *root) {
    emit("// source file: %s\n", ifile);
    emit("import '../sys/s1.dart';\n");
    bool has_main = strstr(source, " main(")!=NULL;
    if (!has_main) emit("void main() {");
    line(0);
    gen_code(root);
    if (!has_main) emit("}");
    emit("\n");
}
