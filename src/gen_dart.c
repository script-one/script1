#define __DART__
#include <gen_j.c>

// class = 'class' id 'extends' eid classBody
static void gen_class(node_t *cid, node_t *eid, node_t *cbody) {
    emit("class ");
    gen_code(cid);

    if (eid) {
        emit(" extends ")
        gen_code(eid);
    }

    emit(" {"); line(0); block_level++;
    for (link_t *p = cbody->list->head; p != NULL; p = p->next) {
        if (p->node->type == Field) {
            indent(block_level);
            emit("var "); // p->node->array[1]=type not handled yet!
            gen_id(p->node->array[0]);
            emit(";");
            line(0);
        } else if (p->node->type == Function) {
            node_t *nasync  = p->node->array[0];
            node_t *nid  = p->node->array[1];
            node_t *nret = p->node->array[2];
            node_t *nparams = p->node->array[3];
            node_t *nbody= p->node->array[4];

            char *name = nid->ptk->str; int len=nid->ptk->len;
            line(nid->ptk->line); indent(block_level); 
            if (head_eq(name, len, "__init")) {
                gen_id(cid);
            } else {
                gen_code(nid);
            }
            // node_t *ntype = nval->array[1], *params = nval->array[2], *block=nval->array[3];
            // if (ntype) gen_code(ntype);
            if (nret) {
                if (nasync) emit("Future<");
                gen_code(nret);
                if (nasync) emit(">");
            }
            gen_code(nparams);
            if (nasync) emit(" async ");
            gen_code(nbody);
            line(0);
        }
    }
    block_level --;
    indent(block_level); emit("}");
}

static void gen_import(node_t *str1, node_t *id2) {
    emit("import ");
    char *fpath = str1->ptk->str + 1;
    int  flen = str1->ptk->len - 2;
    char *ext = fpath + flen - 3;
    if (memcmp(ext, ".s1", 3)==0) {
        emit("'%.*s.dart'", flen-3, fpath);
    } else {
        emit("'%.*s'", flen, fpath);
    }
    if (id2) {
        emit(" as ");
        gen_code(id2);
    }
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    if (n->type == Global) {
        // emit("global['");
        emit("glob['");
    } else if (n->type == This) {
        emit("this.");
    }
    gen_code(n->array[0]);
    if (n->type == Global) {
        emit("']");
    }
}

// assign = (term|pid(:type)?) (= expr)?
static void gen_assign(node_t *term, node_t *type, node_t *exp) {
    // if (type) emit("var ");
    if (type) emit("dynamic ");
    gen_code(term);
    if (exp) {
        emit("=");
        gen_code(exp);
    }
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
static void gen_function(int type, node_t *async, node_t *id, node_t *ret, node_t *params, node_t *body) {
    if (type == Lambda) {
        gen_code(params);
        emit("=>");
        gen_code(body);
    } else {
        if (ret) { gen_code(ret); emit(" "); } else emit("dynamic ");
        gen_code(id); // if (id) gen_code(id);
        gen_code(params);
        if (async) emit(" async ");
        gen_code(body);
    }
}

void gen_dart(node_t *root) {
    emit("// source file: %s\n", ifile);
    emit("import 'package:script1/script1.dart';\n");
    bool has_main = strstr(source, " main(")!=NULL;
    if (!has_main && o_main) emit("void main() {");
    line(0);
    gen_code(root);
    if (!has_main && o_main) emit("}");
    emit("\n");
}
#undef __DART__ 