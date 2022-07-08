#include <s1.h>

static int stack[1000];
static int top = 0;
static int block_level = 0;
static int fn_level = 0;
static bool show_line = true;

static char ebuf[1024], *ep=ebuf;

#define max(a,b) (((a)>(b))?(a):(b))
#define emit(...) { \
  char *lep = ep; \
  sprintf(ep, __VA_ARGS__); ep+=strlen(ep); \
  debug("%.*s", (int) (ep-lep), lep); \
  if (ofp) fprintf(ofp, "%.*s", (int) (ep-lep), lep); \
}

#ifdef __PYTHON__
#define TailComment "#"
#define BlockBegin  " "
#define BlockEnd    " "
#else
#define TailComment "//"
#define BlockBegin  "{"
#define BlockEnd    "}"
#endif

#define line(i) \
  if (show_line) { \
    if (i>0) { \
      int len = 50-(int)(ep-ebuf); \
      emit("%*s", max(len, 0), ""); \
      emit(" %s (%d) \n", TailComment, i); \
    } \
    else { emit("\n"); }; ep = ebuf; \
  }

static void gen_str(node_t *node);
static void gen_num(node_t *node);
static void gen_id(node_t *node);
static void gen_key(node_t *node);
static void gen_op0(int op);
static void gen_op1(int op, node_t *node);
static void gen_op2(node_t *node1, int op, node_t *node2);
static void gen_cexpr(node_t *e1, node_t *e2, node_t *e3);
static void gen_term(node_t *key, node_t *pid, link_t *head);
static void gen_pid(node_t *pid);
static void gen_params(link_t *head);
static void gen_array(link_t *head);
static void gen_pair(node_t *n1, node_t *n2);
static void gen_try(node_t *nbody, node_t *nexp, node_t *ncatch);
static void gen_class(node_t *nid, node_t *eid, node_t *nmap);
static void gen_map(node_t *nmap);
static void gen_args(link_t *head);
static void gen_assign(node_t *pid, node_t *type, node_t *exp);
static void gen_return(int op, node_t *exp);
static void gen_import(node_t *id1, node_t *id2);
static void gen_while(node_t *exp, node_t *stmt);
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2);
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt);
static void gen_function(int type, node_t *async, node_t *id, node_t *ret, node_t *params, node_t *block);
static void gen_block(node_t *block);
static void gen_stmts(node_t *node);
static void gen_stmt(node_t *stmt);
static void gen_code(node_t *me);

static void indent(int level) {
#ifdef __PYTHON__
    emit("%*s", level*4, "");
#else
    emit("%*s", level*2, "");
#endif
}

static void push(int type) {
    stack[top++] = type;
}

static int pop(int type) {
    int p = stack[--top];
    if (p != type) error("pop %d!=%d\n", p, type);
    return type;
}

static int peek() {
    return stack[top-1];
}

static void gen_token(node_t *node) {
    emit("%.*s", node->ptk->len, node->ptk->str);
}

static void gen_list(link_t *head, char *spliter) {
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node);
        if (p->next != NULL) emit("%s", spliter);
    }
}

static void gen_code(node_t *me) {
    node_t **args;
    if (me == NULL) return;
    int type = me->type;
    args = me->array;
    if (type == Stmts) {
        gen_stmts(me);
    } else if (type == Stmt) {
        gen_stmt(me);
    } else if (type == Block) {
        push(Block); block_level++;
        gen_block(me);
        pop(Block);  block_level--;
    } else if (type == Import) {
        gen_import(args[0], args[1]);
    } else if (type == While) {
        push(While);
        gen_while(args[0], args[1]);
        pop(While);
    } else if (type == If) {
        push(If);
        gen_if(args[0], args[1], args[2]);
        pop(If);
    } else if (type == ForIn) {
        push(ForIn);
        gen_for_in(args[0], args[1], args[2]);
        pop(ForIn);
    } else if (type == Function || type == Lambda) {
        push(Function); fn_level++;
        gen_function(type, args[0], args[1], args[2], args[3], args[4]);
        pop(Function);  fn_level--;
    } else if (type == Return || type == '?') {
        gen_return(type, args[0]); // gen_return(type, me->node);
    } else if (type == Continue || type == Break) {
        gen_op0(type); 
    } else if (type == Params) { // params = (param)*
        gen_params(me->list->head);
    } else if (type == Array) {
        gen_array(me->list->head);
    } else if (type == Try) {
        gen_try(args[0], args[1], args[2]);
    } else if (type == Class) {
        gen_class(args[0], args[1], args[2]);
    } else if (type == Map) {
        gen_map(me);
    } else if (type == Args) { // args  = ( expr* )
        gen_args(me->list->head);
    } else if (type == CExpr) { // e1 ? e2 : e3
        gen_cexpr(args[0], args[1], args[2]);
    } else if (type == Term) { // term =  (async|new) pid ([expr] | . id | args )*
        link_t *head = me->list->head;
        node_t *nkey=NULL, *nid=NULL;
        if (head->node->type == Key) {
            nkey = head->node;
            head = head->next;
        } 
        nid = head->node;
        gen_term(nkey, nid, head->next);
    } else if (type == Pid) { // pid = (@|$)? id
        gen_pid(me);
    } else if (type==Assign) {
        gen_assign(args[0], args[1], args[2]);
    } else if (type == Pair) {
        gen_pair(args[0], args[1]);
    } else if (type == Token) {
        gen_token(me);
    } else if (type == Key) {
        gen_key(me);
    } else if (me->len == 0) {
        gen_op0(type);
    } else if (me->len == 1) {
        gen_op1(type, args[0]);
    } else if (me->len == 2) {
        gen_op2(args[0], type, args[1]);
    } else if (type==Id) {
        gen_id(me);
    } else if (type==Num) {
        gen_num(me);
    } else if (type==Str) {
        gen_str(me);
    } else {
        error("gen_code:unknown type=%d=%c", type, type);
    }
}
