#include "map.h"

// 這個 hash 函數比較簡單，但是 R1, R2, R3 這樣的字串會連續，所以不是很好。
// 如果要避免碰撞後搜尋次數太多，可以用更好的 hash 函數
unsigned int map_hash(char *key) {
  char *p = key;
  unsigned int  h = 37;
  while (*p != '\0') {
    h = (h << 4) + h + *p; // h = h*17 + *p; 為了加速不用乘法 ....
    p++;
  }
  return h;
}

map_t* map_new(map_t *map, int size) {
  map->table = calloc(size, sizeof(pair_t));
  map->size = size;
  map->top = 0;
  return map;
}

pair_t *map_find(map_t *map, char *key) {
  int h = map_hash(key) % map->size;
  while (map->table[h].key != NULL) {
    if (strcmp(map->table[h].key, key)==0) break;
    h = (h+1) % map->size;
  }
  return &map->table[h];
}

pair_t* map_add(map_t *map, char *key, void *value) {
  assert(map->top < map->size);
  pair_t *p = map_find(map, key);
  if (p->key == NULL) map->top++;
  p->key = key;
  p->value = value;
  return p;
}

void* map_lookup(map_t *map, char *key) {
  pair_t *p = map_find(map, key);
  if (p->key == NULL) return NULL;
  return p->value;
}

void map_add_all(map_t *map, pair_t *list, int top) {
  for (int i=0; i<top; i++) {
    // printf("%d : key=%s value=%s\n", i, list[i].key, list[i].value);
    map_add(map, list[i].key, list[i].value);
  }
}

void map_dump(map_t *map) {
  printf("======= mapDump() ==============\n");
  for (int i=0; i<map->size; i++) {
    pair_t *p = &map->table[i];
    if (p->key != NULL) {
      printf("%d:  %s %s\n", i, p->key, (char*) p->value);
    }
  }
}

void map_free(map_t *map) {
  free(map->table);
}
