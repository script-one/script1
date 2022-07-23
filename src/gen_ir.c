#include <gen0.c>
#include <vm/ir.c>

static void dump_src(ir_t *irp, int len) {
    char *srcp = ir_src[irp-code];
    char *srcp1 = ir_src[irp+len-code];
    if (srcp < srcp1) {
        emit("// ")
        for (char *p = srcp; p < srcp1; p++) {
            if (*p == '\n') { emit("\\n"); } else { emit("%c", *p); }
        }
        emit("\n");
    }
}

static void dump_ir() {
    // 設定最後一行 source code
    char *src_end = source + strlen(source);
    ir_src[cp-code] = ir_src[cp-code+1] = src_end;
    // 開始 dump 
    ir_t *pc = code, *p = pc;
    while (pc<cp) {
        int i = pc-code;
        int len = ir_op1(*pc)?2:1;
        pc += len;
        if (ir_src[i] < ir_src[i+len]) {
            dump_src(pc-len, len);
        } else
            continue;
        while (p < pc) {
            int pi = p-code;
            ir_t op = *p++;
            char name[20];
            ir_name(op, name);
            emit("%s", name);

            if (op == Float) {
                emit(" %g\t // %d\n", (double) *p++, pi);
            } else if (ir_op1s(op)) {
                emit(" %s\t // %d\n", (char*) *p++, pi);
            } else if (ir_op1d(op)) {
                emit(" %d\t // %d\n", (int) *p++, pi);
            } else {
                emit("\t // %d\n", pi);
            }
        }
    }
}

static int in_param = false;

static void gen_num(node_t *node) {
    char *p = st_token(node->ptk);
    eir(Float); eir(atof(p)); // imm value
}

static void gen_id(node_t *node) {
}

static void gen_str(node_t *node) {
    char *p = st_token(node->ptk);
    eir(Str); eir(p);
}

static void gen_op0(int op) {
}

static void gen_op1(int op, node_t *node) {
    eir(op);
    gen_code(node);
}

static void gen_op2(node_t *node1, int op, node_t *node2) {
    gen_code(node1);
    eir(Push);
    char name[20];
    key_name(op, name);
    gen_code(node2);
    eir(op);
}

// args = ( expr* )
static void gen_args(link_t *head) {
    int narg = 0;
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node);
        eir(Arg);
        narg++;
    }
    eir(Call); eir(narg);
}

// stmt
static void gen_stmt(node_t *stmt) {
    ir_src[cp-code] = stmt->ptk->str; // 指向 stmt 的原始碼位置
    gen_code(stmt->node);
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
    int count=0;
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node);
        eir(Push);
        count ++;
    }
    eir(Array); eir(count);
}

static void gen_key(node_t *node) {
}

static void gen_pair(node_t *n1, node_t *n2) {
    gen_code(n1);
    gen_code(n2);
}

// block = { stmts }
static void gen_block(node_t *block) {
    gen_stmts(block->node); // stmts
}

// while expr stmt
static void gen_while(node_t *exp, node_t *stmt) {
    ir_t *begin = cp;
    gen_code(exp);
    eir(Jz); ir_t *j_end = eir(0); // Jz end
    gen_code(stmt);
    ir_t *end = eir(Jmp)+2; eir(begin-end); // Jmp begin
    *j_end = end - (j_end+1);
}

static void gen_term(node_t *key, node_t *pid, link_t *head) {
    if (key) gen_code(key);
    gen_code(pid);
    for (link_t *p=head; p != NULL; p = p->next) {
        node_t *n = p->node; int op = n->type;
        if (op == '[') {
            gen_code(n->array[0]);
        } else if (op == '.') {
            gen_code(n->array[0]);
        } else if (op == Args) { // function call
            eir(Push);
            gen_code(n);
        }
    }
}

static void gen_map(node_t *nmap) {
    link_t *head = nmap->list->head;
    gen_list(head, ",");
}

// if expr stmt (else stmt)?
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2) {
    gen_code(exp);
    eir(Jz); ir_t *j_else = eir(0);
    ir_t *begin1 = cp;
    gen_code(stmt1);
    eir(Jmp); ir_t *j_end = eir(0);
    ir_t *begin2 = cp;
    *j_else = (ir_t) (begin2-begin1);
    if (stmt2)
       gen_code(stmt2);
    ir_t *end = cp;
    *j_end = (ir_t) (end-begin2);
}

static void gen_cexpr(node_t *e1, node_t *e2, node_t *e3) {
    gen_if(e1, e2, e3);
}

static void gen_try(node_t *nbody, node_t *nexp, node_t *ncatch) {
    gen_code(nbody);
    gen_code(nexp);
    gen_code(ncatch);
}

static void gen_class(node_t *nid, node_t *eid, node_t *nbody) {
    gen_code(nid);
    if (eid) {
        gen_code(eid);
    }
    block_level++;
    gen_list(nbody->list->head, "\n");
    block_level --; 
}

static void gen_import(node_t *str1, node_t *id2) {
    gen_code(str1);
    gen_code(id2);
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    node_t *nid = n->array[0];
    char *name;
    if (n->type == Global) {
        name = st_printf("@%.*s", nid->ptk->len, nid->ptk->str);
    } else if (n->type == This) {
        name = st_printf("$%.*s", nid->ptk->len, nid->ptk->str);
    } else {
        name = st_printf("%.*s", nid->ptk->len, nid->ptk->str);
    }
    gen_code(nid);
    eir(Get), eir(name);
}

// assign = (term|id(:type?)?) (= expr)?
static void gen_assign(node_t *head, node_t *type, node_t *exp) {
    if (head->type == Id) {
        char *name = st_printf("%.*s", head->ptk->len, head->ptk->str);
        if (type || in_param) {
            eir(in_param?Param:Var); eir(name);
            if (type && type->list != NULL)
                gen_list(type->list->head, "");
        } else {
            eir(Get); eir(name); // eir_load(name);
        }
    } else {
        gen_code(head);
    }
    if (exp) {
        eir(Push);
        gen_code(exp);
        eir(Store);
    }
}

static void gen_throw(int op, node_t *exp) {
    gen_code(exp);
    eir(Throw);
}

// (return|?) expr
static void gen_return(int op, node_t *exp) {
    gen_code(exp);
    eir(Ret);
}

static int param_count = 0;

// params = (id(:type?)?=exp)*
static void gen_params(link_t *head) {
    in_param = true;
    param_count = gen_list(head, ",");
    in_param = false;
}

// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    gen_code(id);
    gen_code(exp);
    gen_code(stmt);
}

// function = fn(:id)? id(params) block
static void gen_function(int type, node_t *async, node_t *id, node_t *ret, node_t *params, node_t *block) {
    eir(Fn);
    if (ret) { gen_code(ret); }
    char *sid;
    if (id) {
        gen_code(id);
        sid = st_token(id->ptk);
    } else {
        sid = st_add("_", 1);
    }
    eir(sid);

    gen_code(params);
    eir(Ent); ir_t *ecount = eir(0); // eir(param_count);
    gen_code(block);
    *ecount = fstack[ftop-1].nlocal;
    eir(Lev);
}

void gen_ir(node_t *root) {
    ir_init();
    emit("// source file: %s\n", ifile);
    gen_code(root);

    // append exit(0)
    eir(Get); eir(st_printf("exit")); // get exit
    eir(Push);                        // push
    eir(Call); eir(0);                // call(0)

    emit("\n");
    dump_ir();
}
