#include "map.h"

pair_t jList[] = {
  {"",   "000"}, {"JGT","001"}, {"JEQ","010"}, {"JGE","011"},
  {"JLT","100"}, {"JNE","101"}, {"JLE","110"}, {"JMP","111"}
};

map_t jMap;

int main() {
  map_new(&jMap, 23);
  map_add_all(&jMap, jList, ARRAY_SIZE(jList));
  map_dump(&jMap);
  char *jle = map_lookup(&jMap, "JLE");
  printf("jle=%s\n", jle);
  char *xxx = map_lookup(&jMap, "XXX");
  printf("xxx=%s\n", xxx);
  map_free(&jMap);
}
