#include <gen0.c>
#include <stdint.h>
#include <map.h>
#include <unistd.h>

#define TMAX 10000

typedef struct {
    char *name;
    char type;
    int idx;
} var_t;

map_t sym_table;
var_t vars[TMAX];
int var_top = 0;

word_t code[NMAX], *cp = code, *lcp = code;
word_t data[NMAX], *dp = data;
char stab[NMAX], *stp = stab;

#define eir(c) { *cp++=c; }

static void ir_init() {
  map_new(&sym_table, TMAX);
}

static void ir_close() {
  map_free(&sym_table);
}

static char *st_add(char *str, int len) {
  char *start = stp;
  memcpy(stp, str, len);
  stp += len;
  *stp++ = '\0';
  return start;
}

static var_t* sym_add(char *name) {
  var_t *var = map_lookup(&sym_table, name);
  if (var) return var;
  
  char *vname = st_add(name, strlen(name));

  var = &vars[var_top];
  *var = (var_t) { .name=vname, .type='G', .idx=var_top++ };
  map_add(&sym_table, vname, var);
  // printf("map_add(%s)\n", vname);
  return var;
}

void sym_dump() {
  for (int i=0; i<var_top; i++) {
    var_t *var = &vars[i];
    printf("%s %c %d\n", var->name, var->type, var->idx);
  }
}

static void dump_ir() {
    while (lcp < cp) {
        word_t ir = *lcp++;
        char ir_name[20];
        if (ir >= End) emit("error\n");
        key_name(ir, ir_name);
        emit("%s", ir_name);
        if (ir >= Lea && ir <= Adj) {
            word_t arg = *lcp++;
            emit(" %d", (int) arg);
            if (ir == Var)
                emit(" // %s", vars[arg].name);
            if (ir == Cstr)
                emit(" // '%s'", &stab[arg]);
        }
        emit("\n");
    }
    emit("\n");
}

static void gen_num(node_t *node) {
    int value;
    sscanf(node->ptk->str, "%d", &value);
    eir(Imm); eir(value); // imm value
    gen_token(node);
}

static void gen_id(node_t *node) {
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
        eir(Push);
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
    char *str = node->ptk->str+1; int len = node->ptk->len-2;
    emit("'%.*s'", len, str);
    char *s = st_add(str, len);
    eir(Cstr); eir(s-stab);
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
            eir(Jsr);
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
    char id[100];
    if (n->type == Global) {
        emit("@");
    } else if (n->type == This) {
        emit("$");
    }
    node_t *nid = n->array[0];
    gen_code(nid);

    copy_str(nid->ptk->str, nid->ptk->len, id);
    var_t *var = sym_add(id);
    eir(Var); eir(var->idx); // var id
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
        eir(Push);
        emit("=");
        gen_code(exp);
        eir(Sti);
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

#include <vm.c>

void gen_ir(node_t *root) {
    ir_init();
    emit("// source file: %s\n", ifile);
    line(0);
    gen_code(root);
    emit("\n");
    sym_dump();
    ir_close();
    vm_run(code, 0, NULL);
}
