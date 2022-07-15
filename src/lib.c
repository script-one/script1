#include <stdio.h>
#include <string.h>

// ================= strTable: st_... ==============

char stab[NMAX], *stp = stab;
/*
#define st_printf(...) ({ char *stp0=stp; sprintf(stp, __VA_ARGS__); stp+=strlen(stp)+1; stp0; })
#define st_add(str, len) st_printf("%.*s", (int)(len), (str))
#define st_token(ptk) st_add((ptk)->str, (ptk)->len)
*/

// =================== memory management: pool ================
#define NPTR 100000
void *pools[NPTR];
int poolTop = 0;

void *pool(int size) {
  void *p=malloc(size);
  memset(p, 0, size);
  if (!p) error("pool() alloc fail!");
  pools[poolTop++] = p;
  return p;
}

void pool_init() {
  poolTop = 0;
  memset(pools, 0, sizeof(pools));
}

void pool_free() {
  for (int i=0; i<poolTop; i++) {
    free(pools[i]);
  }
}

// =================== file system ================
int file_size(FILE *fp) {
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}

char *file_read(char *fname) {
    FILE *fp = fopen(fname, "r");
    int sz = file_size(fp);
    char *buf = pool(sz+1);
    int len = fread(buf, 1, sz, fp);
    buf[len] = '\0';
    fclose(fp);
    return buf;
}

bool tail_eq(char *str, char *tail) {
  char *p = str+strlen(str)-strlen(tail);
  return strcmp(p, tail)==0;
}

bool head_eq(char *str, int len, char *head) {
    int hlen = strlen(head);
    return hlen == len && memcmp(str, head, len)==0;
}

void copy_str(char *str, int len, char *to_str) {
    memcpy(to_str, str, len);
    to_str[len] = '\0';
}

// =================== k2i table ================
int k2i(k2i_t *table, int from, int to, char *k, int klen) {
  for (int j=from; j<to; j++) {
    char *kt = table[j].k;
    if (strlen(kt)==klen && memcmp(k, kt, klen)==0)
      return table[j].i;
  }
  return -1;
}

char *i2k(k2i_t *table, int from, int to, int i) {
  for (int j=from; j<to; j++) {
    if (i == table[j].i)
      return table[j].k;
  }
  return NULL;
}

