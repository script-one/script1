#include <s1.h>
#include <lib.c>
#include <init.c>
#include <lex.c>
#include <ast.c>
#include <parse.c>

int main(int argc, char **argv) {
  --argc; ++argv; // skip exe file name
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'l') { o_lex = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 's') { src = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'd') { dbg = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'r') { o_run = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'u') { o_dump = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'm') { o_main = 1; --argc; ++argv; }
  if (argc < 1) { printf("usage: s1 [-s] [-d] [-r] [-u] [-m] in_file [-o] out_file...\n"); return -1; }
  ifile = *argv;
  if (argc > 1) {
    char *narg = *(argv+1);
    if (*narg == '-' && narg[1] == 'o') {
      ofile = *(argv+2);
    }
  }
  pool_init();
  p = lp = source = file_read(ifile);
  if (!source) error("%s not exist!\n", ifile);
  // printf("%s", source);
  if (o_lex) { lex(source); return 1; }
  node_t *ast = parse(source);
  if (ofile) ofp = fopen(ofile, "w"); else ofp = stdout;
  if (!ofile) {}
  else if (tail_eq(ofile, ".s1")) gen_s1(ast);
  else if (tail_eq(ofile, ".js")) gen_js(ast);
  else if (tail_eq(ofile, ".dart")) gen_dart(ast);
  else if (tail_eq(ofile, ".py")) gen_py(ast);
  else if (tail_eq(ofile, ".cpp")) gen_cpp(ast);
  else if (tail_eq(ofile, ".ir")) gen_ir(ast);
  else error("%s: file type not supported!\n", ofile);
  pool_free();
  return 0;
}
