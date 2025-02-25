#include "HashMap.h"
#include "../global_allocator.h"

//If you do not use "hashmap_insert_copy" you can set copy_key and copy_value to NULL
HashMap create_hashmap(size_t init_cap, size_t (*hash_key)(void *key), int32_t (*compare_key)(void *key1, void *key2), void *(*copy_key)(void *), void *(*copy_value)(void *)) {
    HashMap hm;
    hm.buckets = allocate(init_cap * sizeof(HashNode *));
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
                deallocate(curr->key);
                deallocate(curr->value);
            }
            deallocate(curr);
        }
    }
    deallocate(map->buckets);
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
    HashNode *hn = allocate(sizeof(HashNode));
    hn->next = NULL;
    hn->key = key;
    hn->value = value;
    hn->should_dealloc = should_dealloc;
    return hn;
}

void hashmap_resize(HashMap *map) {
    if (!map) return;

    // Define a nova capacidade (dobrando o tamanho atual)
    size_t new_capacity = map->capacity * 2;

    // Aloca um novo array de buckets
    HashNode **new_buckets = allocate(new_capacity * sizeof(HashNode *));
    if (!new_buckets) {
        fprintf(stderr, "Falha ao alocar memória para novos buckets.\n");
        exit(1);
    }

    // Inicializa os novos buckets como NULL
    for (size_t i = 0; i < new_capacity; i++) {
        new_buckets[i] = NULL;
    }

    // Redistribui os elementos no novo array de buckets
    for (size_t i = 0; i < map->capacity; i++) {
        HashNode *node = map->buckets[i];
        while (node) {
            HashNode *next = node->next;

            // Recalcula o índice no novo array
            size_t new_index = map->hash(node->key) % new_capacity;

            // Insere o nó no novo bucket
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;

            node = next;
        }
    }

    // Libera o array antigo e atualiza o hashmap
    deallocate(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;
}

void hashmap_insert_move(HashMap *map, void *key, void* value) {
    if (!map || !key || !value) return;

    if(map->size / map->capacity > LOAD_FACTOR) {
        hashmap_resize(map);
    }

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
                deallocate(aux->key);
                deallocate(aux->value);
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

    if(map->size / map->capacity > LOAD_FACTOR) {
        hashmap_resize(map);
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
                deallocate(aux->key);
                deallocate(aux->value);
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
