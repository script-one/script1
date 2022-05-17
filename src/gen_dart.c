#include <gen_j.c>

static void gen_str(node_t *node) {
    emit("'%.*s'", node->ptk->len-2, node->ptk->str+1);
}

// class = 'class' id map
static void gen_class(node_t *nid, node_t *nmap) {
    emit("class ");
    gen_code(nid);
    emit(" {"); /*line(0);*/ block_level++;
    for (link_t *p = nmap->list->head; p != NULL; p = p->next) {
        ok(p->node->type == Pair);
        node_t *nkey = p->node->array[0];
        node_t *nval = p->node->array[1];
        if (nval->type == Function) {
            char *name = nkey->ptk->str; int len=nkey->ptk->len;
            line(nkey->ptk->line); indent(block_level); 
            if (head_eq(name, len, "__init")) {
                emit("constructor");
            } else {
                gen_code(nkey);
            }
            node_t *params = nval->array[1], *block=nval->array[2];
            gen_code(params);
            gen_code(block);
        }
        line(0);
    }
    block_level --;
    indent(block_level); emit("}");
}

// map = [ (expr:expr)* ]
static void gen_map(node_t *nmap) {
    emit("{");
    link_t *head = nmap->list->head;
    gen_list(head, ",");
    emit("}");
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
        emit("global.");
    } else if (n->type == This) {
        emit("this.");
    }
    gen_code(n->array[0]);
}

// (await|new)? pid ( [expr] | . id | args )*
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
static void gen_function(node_t *id, node_t *ret, node_t *params, node_t *block) {
    if (ret) { gen_code(ret); emit(" "); } else emit("void ");
    if (id) gen_code(id);
    gen_code(params);
    gen_code(block);
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
