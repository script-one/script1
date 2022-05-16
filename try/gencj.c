#include <s1.h>
#include <gen_cj.c>

int main(int argc, char **argv) {
    read_source(argv[1]);
    src = true;
    node_t *ast=parse(source);
    gen_code(ast);
}
