#include "HashMap.h"
#include "../global_allocator.h"

//If you do not use "hashmap_insert_copy" you can set copy_key and copy_value to NULL
HashMap create_hashmap(size_t init_cap, size_t (*hash_key)(void *key), int32_t (*compare_key)(void *key1, void *key2), void *(*copy_key)(void *), void *(*copy_value)(void *)) {
    HashMap hm;
    hm.buckets = alloc(init_cap * sizeof(HashNode *));
    if (!hm.buckets) {
        fprintf(stderr, "Falha ao alocar memória para buckets.\n");
        exit(1);
    }
    // Inicializa todos os buckets como NULL
    for (size_t i = 0; i < init_cap; i++) {
        hm.buckets[i] = NULL;
    }
    hm.capacity = init_cap;
    hm.size = 0;
    hm.hash = hash_key;
    hm.cmp = compare_key;
    hm.copy_key = copy_key;
    hm.copy_value = copy_value;
    return hm;
}
void delete_hashmap(HashMap *map) {
    if (!map) return;
    for(size_t i = 0; i < map->capacity; i++) {
        HashNode *aux = map->buckets[i];
        while(aux) {
            HashNode *curr = aux;
            aux = aux->next;
            if(curr->should_dealloc) {
                dealloc(curr->key);
                dealloc(curr->value);
            }
            dealloc(curr);
        }
    }
    dealloc(map->buckets);
    map->buckets = NULL;
    map->capacity = 0;
    map->size = 0;
}


size_t hash_cstr(void *data) {
    char *str = (char *)data;
    size_t hash = 5381; // Valor inicial (escolhido empiricamente)
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
size_t hash_uint64(void *data) {
    return (size_t)(*(uint64_t *)data * 2654435761);
}
size_t hash_int64(void *data) {
    return (size_t)(*(int64_t *)data * 2654435761);
}
size_t hash_bool(void *data) {
    return (size_t)*(bool *)data;
}

int32_t cmp_cstr(void *x, void *y) {
    return strcmp((char *)x, (char *)y);
}

int32_t cmp_int64(void *x, void *y) {
    return *(int64_t *)x - *(int64_t *)y;
}

int32_t cmp_uint64(void *x, void *y) {
    return *(uint64_t *)x - *(uint64_t *)y;
}

int32_t cmp_bool(void *x, void *y) {
    return *(bool *)x - *(bool *)y;
}


HashNode *new_hash_node(void *key, void *value, bool should_dealloc) {
    HashNode *hn = alloc(sizeof(HashNode));
    hn->key = key;
    hn->value = value;
    hn->should_dealloc = should_dealloc;
    return hn;
}

void hashmap_insert_move(HashMap *map, void *key, void* value) {
    if (!map || !key || !value) return;
    size_t index = map->hash(key) % map->capacity;
    HashNode *aux = map->buckets[index];
    if(aux == NULL) {
        map->buckets[index] = new_hash_node(key, value, false);
        map->size++;
        return;
    }
    while(aux) {
        if(!map->cmp(aux->key, key)) {
            if(aux->should_dealloc) {
                dealloc(aux->key);
                dealloc(aux->value);
            }
            aux->key = key;
            aux->value = value;
            aux->should_dealloc = false;
            map->size++;
            break;
        }
        if(aux->next == NULL) {
            aux->next = new_hash_node(key, value, false);
            map->size++;
            break;
        }
        aux = aux->next;
    }
}


void hashmap_insert_copy(HashMap *map, void *key, void *value) {
    if (!map || !key || !value) return;

    if (!map->copy_key || !map->copy_value) {
        fprintf(stderr, "Copy key ou copy value são NULL. Use \"create_hashmap\" e defina funções para copiar a chave e o valor.\n");
        exit(1);
    }
    size_t index = map->hash(key) % map->capacity;
    HashNode *aux = map->buckets[index];
    if(aux == NULL) {
        map->buckets[index] = new_hash_node(map->copy_key(key), map->copy_value(value), true);
        map->size++;

        return;
    }
    while(aux) {
        if(!map->cmp(aux->key, key)) {
            if(aux->should_dealloc) {
                dealloc(aux->key);
                dealloc(aux->value);
            }
            aux->key = map->copy_key(key);
            aux->value = map->copy_value(value);
            aux->should_dealloc = true;

            break;
        }
        if(aux->next == NULL) {
            aux->next = new_hash_node(map->copy_key(key), map->copy_value(value), true);
            map->size++;

            break;
        }
        aux = aux->next;
    }
}

void *hashmap_get(HashMap *map, void *key) {
    if (!map || !key) return NULL;
    size_t index = map->hash(key) %map->capacity;
    HashNode *aux = map->buckets[index];
    while(aux) {
        if(!map->cmp(aux->key, key)) {
            return aux->value;
        }
        aux = aux->next;
    }
    return NULL;
}
