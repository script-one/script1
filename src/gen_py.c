#define __PYTHON__
#include <gen1.c>

// if expr stmt (else stmt)?
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2) {
    emit("if "); gen_code(exp);
    emit(":");
    gen_code(stmt1);
    if (stmt2) {
        emit("  else");
        emit(":");
        gen_code(stmt2);
    }
}

static void gen_cexpr(node_t *e1, node_t *e2, node_t *e3) {
    gen_code(e2);
    emit(" if ");
    gen_code(e1);
    emit(" else ");
    gen_code(e3);
}

static void gen_str(node_t *node) {
    emit("\'%.*s\'", node->ptk->len-2, node->ptk->str+1);
}

// class = 'class' id map
static void gen_class(node_t *cid, node_t *cbody) {
    emit("class ");
    gen_code(cid);
    emit(": "); line(0); block_level++;
    for (link_t *p = cbody->list->head; p != NULL; p = p->next) {
        if (p->node->type == Id) {
            indent(block_level);
            line(0);
        } else if (p->node->type == Function) {
            node_t *nasync  = p->node->array[0];
            node_t *nid  = p->node->array[1];
            node_t *nret = p->node->array[2];
            node_t *nparams = p->node->array[3];
            node_t *nbody= p->node->array[4];

            char *name = nid->ptk->str; int len=nid->ptk->len;
            line(nid->ptk->line); indent(block_level);
            if (nasync) emit("async ");  
            if (head_eq(name, len, "__init")) {
                // gen_id(cid);
                emit("def __init__")
            } else {
                emit("def ");gen_code(nid);emit("__");
            }
            if (nret) gen_code(nret);
            // node_t Self;
            // Self.type = This;
            emit("(");
            emit("self, ");
            // gen_params(nparams);
            gen_list(nparams->list->head, ",");
            emit(")");
            emit(":")
            gen_code(nbody);
            line(0);
        }
    }
    block_level --;
    indent(block_level);
}

// map = [ (str:expr)* ]
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
    // gen_code(str1);
    emit("'%.*s'", str1->ptk->len-2, str1->ptk->str+1);
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    if (n->type == Global) {
        emit("global.");
    } else if (n->type == This) {
        emit("self.");
    }
    gen_code(n->array[0]);
}

// (await|new)? pid ( [expr] | . id | args )*
static void gen_term(node_t *key, node_t *pid, link_t *head) {
    if (key) {
        // gen_code(key);
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

// while expr stmt
static void gen_while(node_t *exp, node_t *stmt) {
    emit("while "); 
    gen_code(exp);
    emit(":");
    gen_code(stmt);
}

// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    emit("for ");
    gen_code(id);
    emit(" in ");
    gen_code(exp);
    emit(":");
    gen_code(stmt);
}
static void gen_function(int type, node_t *async, node_t *id, node_t *ret, node_t *params, node_t *block) {
    if (async) emit("async ");
    if (id){
        emit("def ");
        gen_code(id);
        gen_code(params);
        emit(":");
        gen_code(block);
    } else {
        emit("lambda ");
        gen_list(params->list->head, ",");
        emit(":");
        gen_code(block);
    }
}

static void gen_try(node_t *nbody, node_t *nexp, node_t *ncatch) {
    emit("try: ");
    gen_code(nbody);
    emit("except ");
    gen_code(nexp);
    emit(": ");
    gen_code(ncatch);
}

void gen_py(node_t *root) {
    emit("# source file: %s\n", ifile);
    emit("import sys, os\nsys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))\n");
    emit("from s1 import *\n");
    line(0);
    gen_code(root);
    emit("\n");
}

#undef __PYTHON__