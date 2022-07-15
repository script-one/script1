#include <obj.c>

word_t vm_stack[NMAX];

int vm_run(word_t *pc, int argc, char *argv[]) { // 虛擬機 => pc: 程式計數器, sp: 堆疊暫存器, bp: 框架暫存器
  word_t i, *sp; // *bp, a: 累積器, cycle: 執行指令數
  obj_t *a; //, *t;
  int cycle;    // temps

  // setup stack
  /*bp =*/ sp = vm_stack+NMAX;
  /*
  *--sp = Exit; // call exit if main returns
  *--sp = Push; t = sp;
  *--sp = argc;
  *--sp = (word_t)argv;
  *--sp = (word_t)t;
  */
  cycle = 0;
  while (1) {
    i = *pc++; ++cycle;
    if (dbg) {
      char op_name[100];
      key_name(i, op_name);
      printf("%d> %s", cycle, op_name);
      if (i>VmOpBegin && i <= Adj) printf(" %d\n", (int) *pc); else printf("\n");
    }
    
    /*if      (i == Lea) a = (word_t)(bp + *pc++);                             // load local address 載入區域變數
    else if (i == Jsr) { // jump to subroutine 跳到副程式
        *--sp = (word_t)(pc + 1); // 推返回點入堆疊
        pc = (word_t *)*pc; // goto 副程式
    }
    else if (i == Narg) {
        word_t n = *pc++;
        for (int i=0; i<n; i++) {
            word_t arg = *sp++;
            printf("  pop %p\n", (word_t*) arg);
        }
    }
    // else if (i == Imm) a = *pc++;                                         // load global address or immediate 載入全域變數或立即值
    else */ if (i == Double) {
        a = obj_new(TDOUBLE);
        a->dvalue = *pc++;
    }
    // else if (i == Int) a = *pc++;                                         // load global address or immediate 載入全域變數或立即值
    else if (i == Var) a = &obj[vars[*pc++].idx];                                         // load global address or immediate 載入全域變數或立即值
    else if (i == Cstr) {
        a = obj_new(TSTRING);
        a->str = &stab[*pc++];                                     // load global address or immediate 載入全域變數或立即值
    }
    // else if (i == Jmp) pc = (word_t *)*pc;                                   // jump               躍躍指令
    // else if (i == Bz)  pc = a ? pc + 1 : (word_t *)*pc;                      // branch if zero     if (a==0) goto m[pc]
    // else if (i == Bnz) pc = a ? (word_t *)*pc : pc + 1;                      // branch if not zero if (a!=0) goto m[pc]
    // else if (i == Ent) { *--sp = (word_t)bp; bp = sp; sp = sp - *pc++; }     // enter subroutine   進入副程式
    // else if (i == Adj) sp = sp + *pc++;                                   // stack adjust       調整堆疊
    // else if (i == Lev) { sp = bp; bp = (word_t *)*sp++; pc = (word_t *)*sp++; } // leave subroutine   離開副程式
    // else if (i == Load) {
    //     int idx = (word_t *)a;  
    //     a = *                                   // load int           載入整數
    // else if (i == Ldc)  a = *(char *)a;                                    // load char          載入字元
    // else if (i == Sti)  *(word_t *)*sp++ = a;                                 // store int          儲存整數
    // else if (i == Stb)  a = *(char *)*sp++ = a;                            // store char         儲存字元
    //else if (i == Pop) {
    //    a = *sp++;
    // }
    else if (i == Push) {
        *--sp = (word_t) a;                                         // push               推入堆疊
    }
    // else if (i == '|')  a = *sp++ |  a; // a = a OR *sp
    // else if (i == '^') a = *sp++ ^  a; // a = a XOR *sp
    // else if (i == '&') a = *sp++ &  a; // ...
    // else if (i == '=')  a = *sp++ == a;
    // else if (i == Neq)  a = *sp++ != a;
    // else if (i == '<')  a = *sp++ <  a;
    // else if (i == '>')  a = *sp++ >  a;
    // else if (i == Le)  a = *sp++ <= a;
    // else if (i == Ge)  a = *sp++ >= a;
    // else if (i == Shl) a = *sp++ << a;
    // else if (i == Shr) a = *sp++ >> a;
    // else if (i == '+') a = *sp++ +  a;
    // else if (i == '-') a = *sp++ -  a;
    // else if (i == '*') a = *sp++ *  a;
    // else if (i == '/') a = *sp++ /  a;
    // else if (i == '%') a = *sp++ %  a;

    // else if (i == Open) a = open((char *)sp[1], *sp); // 開檔
    // else if (i == Read) a = read(sp[2], (char *)sp[1], *sp); // 讀檔
    // else if (i == Close) a = close(*sp); // 關檔
    else if (i == Narg) {
        // 取 n 個參數接再一起形成 arguments

    }
    else if (i == Print) {
        a = (obj_t*) *sp++; // pop arguments
        obj_print(a);
        // t = sp + pc[1];
        // a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]);
    }
    // else if (i == Malc) a = (word_t)malloc(*sp); // 分配記憶體
    // else if (i == Free) free((void *)*sp); // 釋放記憶體
    // else if (i == Mset) a = (word_t)memset((char *)sp[2], sp[1], *sp); // 設定記憶體
    // else if (i == Mcmp) a = memcmp((char *)sp[2], (char *)sp[1], *sp); // 比較記憶體
    else if (i == Exit) { printf("exit(%d) cycle = %d\n", (int) *sp, cycle); return *sp; } // EXIT 離開
    else { printf("unknown instruction = %d! cycle = %d\n", (int) i, cycle); return -1; } // 錯誤處理
  }
}
