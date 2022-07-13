#include <stdio.h>
#include <string.h>

int find(char *keys[], int size, char *name, int len) {
  for (int i=0; i<size; i++) {
    if (strlen(keys[i])==len && memcmp(name, keys[i], len)==0)
      return i;
  }
  return -1;
}

int main() {
  char *ops[] = {"+", "-", "==", "!=", "<=", ">="};
  int size = sizeof(ops)/sizeof(char*);
  printf("find(>=)=%d\n", find(ops, size, ">=", 2));
  printf("find(x)=%d\n", find(ops, size, "x", 1));
}
