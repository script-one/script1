#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stab[1000], *stp = stab, *start1;

#define st_printf(...) ({ start1=stp; sprintf(stp, __VA_ARGS__); stp+=strlen(stp); start1; })

int main() {
    char *s = st_printf("name=%s age=%d\n", "ccc", 52);
    printf("s=%s", s);
}
