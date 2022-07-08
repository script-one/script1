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
} Pair;

typedef struct _Map {
  Pair *table;
  int size;
  int top;
} Map;

#define ARRAY_SIZE(list) (sizeof(list)/sizeof(list[0]))
extern unsigned int hash(char *key);
extern Map* map_new(Map *map, int size);
extern Pair* map_find(Map *map, char *key);
extern Pair* map_add(Map *map, char *key, void *value);
extern void map_add_all(Map *map, Pair *list, int top);
extern void* map_lookup(Map *map, char *key);
extern void map_dump(Map *map);
extern void map_free(Map *map);

#endif
