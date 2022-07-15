#include <gen0.c>
#include <ir.c>
#include <env.c>

static void dump_ir() {
    while (lcp < cp) {
        ir_t op = *lcp++;
        char name[20];
        if (op >= End) emit("error\n");
        op_name(op, name);
        emit("%s", name);
        ir_t arg;
        if (op == Str || op == Float || op == Get || op == Var || op == Param || op == Fn || op == Src) {
            arg = *lcp++;
            emit(" %s", (char*) arg);
        } else if (op == Local || op == Narg || op == Ent || op == Jmp || op == Bz || op == Bnz || op == Adj ) {
            arg = *lcp++;
            emit(" %d", (int) arg);
        }
        emit("\n");
    }
    emit("\n");
}

// 產生載入變數的指令，可能是 load name 或 local i
void eir_load(char *name) {
    int local_idx = env_findlocal(name);
    if (local_idx == 0) { // not found!
        eir(Get); eir(name); // get name
    } else {
        eir(Local); eir(local_idx); // local i
    }
}

static int in_param = false;

static void gen_num(node_t *node) {
    char *p = st_token(node->ptk);
    eir(Float); eir(p); // imm value
    gen_token(node);
}

static void gen_id(node_t *node) {
    gen_token(node);
}

static void gen_str(node_t *node) {
    emit("%.*s", node->ptk->len, node->ptk->str);
    char *p = st_token(node->ptk);
    eir(Str); eir(p);
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
    eir(op);
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
        eir(Arg); // eir(Push);
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
    char *start=stmt->ptk->str, *end = strchr(start, '\n');
    char *p = st_printf("%d:%.*s", stmt->ptk->line, (int) (end-start), start); 
    eir(Src); eir(p);
    emit("// "); // source as comment
    if (top == 0 || peek() == Block) {
        indent(block_level);
    } else {
        emit(" ");
    }
    gen_code(stmt->node);
    if (semicolon()) emit(";");
    line(stmt->ptk->line);
    // dump_ir();
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
    emit("// "); indent(block_level-1); emit(BlockBegin); line(block->ptk->line);
    gen_stmts(block->node); // stmts
    emit("// "); indent(block_level-1); emit(BlockEnd);
}

// while expr stmt
static void gen_while(node_t *exp, node_t *stmt) {
    ir_t *begin = cp, *b;
    emit("while ");
    gen_code(exp);
    eir(Bz); b = cp; eir(0);
    gen_code(stmt);
    eir(Jmp); eir(begin-cp);
    *b = cp - b;
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
            eir(Call);
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
    eir(Bz); ir_t *b_else = cp; eir(0);
    emit("?");
    gen_code(e2);
    *b_else = (ir_t) (cp-b_else);
    eir(Jmp); ir_t *b_end = cp; eir(0);
    emit(":");
    gen_code(e3);
    *b_end = (ir_t) (cp-b_end);
}

// if expr stmt (else stmt)?
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2) {
    emit("if "); gen_code(exp);
    eir(Bz); ir_t *b_else = cp; eir(0);
    gen_code(stmt1);
    eir(Jmp); ir_t *b_end = cp; eir(0);
    if (stmt2) {
        *b_else = (ir_t) (cp-b_else);
        emit(" else");
        gen_code(stmt2);
    } else {
        *b_else = (ir_t) (cp-b_else);
    }
    *b_end = (ir_t) (cp-b_end);
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
    char *name;
    if (n->type == Global) {
        emit("@");
        name = st_printf("@%.*s", nid->ptk->len, nid->ptk->str);
    } else if (n->type == This) {
        emit("$");
        name = st_printf("$%.*s", nid->ptk->len, nid->ptk->str);
    } else {
        name = st_printf("%.*s", nid->ptk->len, nid->ptk->str);
    }
    gen_code(nid);
    eir_load(name);
}

// assign = (term|id(:type?)?) (= expr)?
static void gen_assign(node_t *head, node_t *type, node_t *exp) {
    if (head->type == Id) {
        char *name = st_printf("%.*s", head->ptk->len, head->ptk->str);
        emit(name);
        if (type || in_param) {
            eir(in_param?Param:Var); eir(name);
            env_pushvar(name); // 新增該變數到環境中
            emit(":");
            if (type && type->list != NULL)
                gen_list(type->list->head, "");
        } else {
            eir_load(name);
        }
    } else {
        gen_code(head);
    }
    if (exp) {
        emit("=");
        eir(Push);
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
    eir(Ret);
}

static int param_count = 0;
// params = (id(:type?)?=exp)*
static void gen_params(link_t *head) {
    in_param = true;
    emit("(");
    param_count = gen_list(head, ",");
    emit(")");
    in_param = false;
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
    emit("fn"); eir(Fn);
    if (ret) { emit(":"); gen_code(ret); }
    emit(" ");
    char *sid;
    if (id) {
        gen_code(id);
        sid = st_token(id->ptk);
    } else {
        sid = st_add("_", 1);
    }
    eir(sid);

    env_pushf(sid); // 新增函數堆疊，將參數加入其中
    gen_code(params);
    env_params_end();
    // f->local_start = var_top; // 紀錄區域變數起始點
    eir(Ent); eir(param_count);
    gen_code(block);
    env_popf();
    eir(Lev);
}

void gen_ir(node_t *root) {
    emit("// source file: %s\n", ifile);
    line(0);
    env_init();
    gen_code(root);
    emit("\n");
    dump_ir();
}
