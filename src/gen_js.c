#define __JAVASCRIPT__
#include <gen_j.c>

// class = 'class' id 'extends' eid classBody
static void gen_class(node_t *nid, node_t *eid, node_t *nbody) {
    emit("class ");
    gen_code(nid);

    if (eid) {
        emit(" extends ")
        gen_code(eid);
    }
    
    emit(" {"); /*line(0);*/ block_level++;
    for (link_t *p = nbody->list->head; p != NULL; p = p->next) {
        if (p->node->type != Function) continue;
        node_t *nasync  = p->node->array[0];
        node_t *nid  = p->node->array[1];
        node_t *nret = p->node->array[2];
        node_t *nparams = p->node->array[3];
        node_t *nbody= p->node->array[4];

        char *name = nid->ptk->str; int len=nid->ptk->len;
        line(nid->ptk->line); indent(block_level);
        if (nasync) emit("async "); 
        if (head_eq(name, len, "__init")) {
            emit("constructor");
        } else {
            gen_code(nid);
        }
        if (nret) gen_code(nret);
        gen_code(nparams);
        if (eid && head_eq(name, len, "__init")) {
            emit("{\n");
            emit("\tsuper();\n");
            link_t *head = nbody->node->list->head;
            gen_list(head, ",");
            emit("}");
        } else {
            gen_code(nbody);
        }

        line(0);
    }
    block_level --;
    indent(block_level); emit("}");
}

static void gen_import(node_t *str1, node_t *id2) {
    emit("import * as ");
    gen_code(id2);
    emit(" from ");
    char *fpath = str1->ptk->str + 1;
    int  flen = str1->ptk->len - 2;
    char *ext = fpath + flen - 3;
    if (memcmp(ext, ".s1", 3)==0) {
        emit("'%.*s.js'", flen-3, fpath);
    } else {
        emit("'%.*s'", flen, fpath);
    }
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    if (n->type == Global) {
        emit("glob.");
    } else if (n->type == This) {
        emit("this.");
    }
    gen_code(n->array[0]);
}

// assign = (term|pid(:type)?) (= expr)?
static void gen_assign(node_t *term, node_t *type, node_t *exp) {
    if (type) emit("let ");
    gen_code(term);
    if (exp) {
        emit("=");
        gen_code(exp);
    }
}

/*
// params = assign*
static void gen_params(link_t *head) {
    emit("(");
    for (link_t *p = head; p != NULL; p = p->next) {
        node_t *nid = p->node->array[0];
        node_t *nexp = p->node->array[2];
        gen_code(nid);
        if (nexp) {
            emit("=");
            gen_code(p->node->array[2]);
        }
        if (p->next != NULL) emit(",");
    }
    emit(")");
}

// field = id(:type?)?
static void gen_field(node_t *nid, node_t *ntype) {
    gen_code(nid);
}
*/

/*
// params = param*; 
static void gen_params(link_t *head) {
    emit("(");
    gen_list(head, ",");
    emit(")");
}
*/
// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    emit("for (let ");
    gen_code(id);
    emit(" of ");
    gen_code(exp);
    emit(")");
    gen_code(stmt);
}

// function = fn id?(params) body
static void gen_function(int type, node_t *async, node_t *id, node_t *ret, node_t *params, node_t *body) {
    if (type == Lambda) {
        gen_code(params);
        emit("=>");
        gen_code(body);
    } else {
        emit("export ");
        if (async) emit("async ");
        emit("function ");
        gen_code(id);
        gen_code(params);
        gen_code(body);
    }
}

void gen_js(node_t *root) {
    emit("// source file: %s\n", ifile);
    if (o_main) emit("import '../sys/s1.js'\n");
    line(0);
    gen_code(root);
    if (o_main) emit("if (typeof main == 'function') main()");
    emit("\n");
}
#undef __JAVASCRIPT__