#define TMAX 100000

typedef struct {
    char *name;
    void *value;
} Symbol_t;

char str_table[TMAX];
char *sym_table[TMAX];

int find(char *name, int len) {

}

int add(char *name, int len) {
    int si = find(name, len);
    if (si < 0)
}

