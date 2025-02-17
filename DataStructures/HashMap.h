#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct HashMap HashMap;
typedef struct HashNode HashNode;

#define INIT_CAP 16
#define LOAD_FACTOR 0.75

struct HashNode {
    void *key;
    void *value;
    bool should_dealloc;
    HashNode *next;
};

struct HashMap {
    HashNode **buckets;
    size_t capacity;
    size_t size;
    size_t (*hash)(void *data);
    int32_t (*cmp)(void *x, void *y);
    void *(*copy_key)(void *key);
    void *(*copy_value)(void *value);
};

HashMap create_hashmap(size_t init_cap, size_t (*hash_key)(void *key), int32_t (*compare_key)(void *key1, void *key2), void *(*copy_key)(void *), void *(*copy_value)(void *));
void delete_hashmap(HashMap *map);

size_t hash_cstr(void *data);
size_t hash_uint64(void *data);
size_t hash_int64(void *data);
size_t hash_bool(void *data);

int32_t cmp_cstr(void *x, void *y);
int32_t cmp_uint64(void *x, void *y);
int32_t cmp_int64(void *x, void *y);
int32_t cmp_bool(void *x, void *y);

void hashmap_insert_move(HashMap *map, void *key, void *value);
void hashmap_insert_copy(HashMap *map, void *key, void *value);
void *hashmap_get(HashMap *map, void *key);

#endif /* HASHMAP_H */