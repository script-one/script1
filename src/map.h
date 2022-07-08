#ifndef __MAP_H__
#define __MAP_H__

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct _Pair {
  char *key;
  void *value;
} pair_t;

typedef struct _Map {
  pair_t *table;
  int size;
  int top;
} map_t;

#define ARRAY_SIZE(list) (sizeof(list)/sizeof(list[0]))
extern unsigned int map_hash(char *key);
extern map_t* map_new(map_t *map, int size);
extern pair_t* map_find(map_t *map, char *key);
extern pair_t* map_add(map_t *map, char *key, void *value);
extern void map_add_all(map_t *map, pair_t *list, int top);
extern void* map_lookup(map_t *map, char *key);
extern void map_dump(map_t *map);
extern void map_free(map_t *map);

#endif
