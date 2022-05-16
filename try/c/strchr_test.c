#include <stdio.h>
#include <string.h>

int main() {
  int c = 58;
  char *t;
  if (t=strchr("=:", c))
    printf("t=%d\n", t);
}
