#include <stdio.h>

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
