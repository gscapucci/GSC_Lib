#ifndef HASHMAP_TEST_H
#define HASHMAP_TEST_H

#include "../GSC_Lib.h"

#define INIT_CAP 16

// Funções auxiliares para copiar chaves e valores
void *copy_string(void *key) {
    char *str = (char *)key;
    char *copy = allocate(strlen(str) + 1);
    strcpy(copy, str);
    return copy;
}

void *copy_int(void *value) {
    int *copy = allocate(sizeof(int));
    *copy = *(int *)value;
    return copy;
}

// Funções de teste
void test_create_hashmap() {
    HashMap map = create_hashmap(INIT_CAP, hash_cstr, cmp_cstr, copy_string, copy_int);
    assert(map.capacity == INIT_CAP);
    assert(map.size == 0);
    assert(map.hash != NULL);
    assert(map.cmp != NULL);
    assert(map.copy_key != NULL);
    assert(map.copy_value != NULL);
    delete_hashmap(&map);
    printf("test_create_hashmap passed!\n");
}

void test_hashmap_insert_move() {
    HashMap map = create_hashmap(INIT_CAP, hash_cstr, cmp_cstr, NULL, NULL);

    char key1[] = "key1";
    int value1 = 10;
    hashmap_insert_move(&map, key1, &value1);

    char key2[] = "key2";
    int value2 = 20;
    hashmap_insert_move(&map, key2, &value2);

    assert(map.size == 2);
    assert(*(int *)hashmap_get(&map, key1) == 10);
    assert(*(int *)hashmap_get(&map, key2) == 20);

    delete_hashmap(&map);
    printf("test_hashmap_insert_move passed!\n");
}

void test_hashmap_insert_copy() {
    HashMap map = create_hashmap(INIT_CAP, hash_cstr, cmp_cstr, copy_string, copy_int);

    char key1[] = "key1";
    int value1 = 10;
    hashmap_insert_copy(&map, key1, &value1);

    char key2[] = "key2";
    int value2 = 20;
    hashmap_insert_copy(&map, key2, &value2);

    assert(map.size == 2);
    assert(*(int *)hashmap_get(&map, key1) == 10);
    assert(*(int *)hashmap_get(&map, key2) == 20);

    delete_hashmap(&map);
    printf("test_hashmap_insert_copy passed!\n");
}

void test_hashmap_get() {
    HashMap map = create_hashmap(INIT_CAP, hash_cstr, cmp_cstr, copy_string, copy_int);

    char key1[] = "key1";
    int value1 = 10;
    hashmap_insert_copy(&map, key1, &value1);

    char key2[] = "key2";
    int value2 = 20;
    hashmap_insert_copy(&map, key2, &value2);

    assert(*(int *)hashmap_get(&map, key1) == 10);
    assert(*(int *)hashmap_get(&map, key2) == 20);
    assert(hashmap_get(&map, "nonexistent_key") == NULL);

    delete_hashmap(&map);
    printf("test_hashmap_get passed!\n");
}

void test_hashmap_collision() {
    HashMap map = create_hashmap(INIT_CAP, hash_cstr, cmp_cstr, copy_string, copy_int);

    // Dois valores com a mesma chave (simulando colisão)
    char key1[] = "key1";
    int value1 = 10;
    hashmap_insert_copy(&map, key1, &value1);

    char key2[] = "key1"; // Mesma chave
    int value2 = 20;
    hashmap_insert_copy(&map, key2, &value2);

    // O valor deve ser sobrescrito
    assert(map.size == 1);
    assert(*(int *)hashmap_get(&map, key1) == 20);

    delete_hashmap(&map);
    printf("test_hashmap_collision passed!\n");
}

void test_hashmap_delete() {
    HashMap map = create_hashmap(INIT_CAP, hash_cstr, cmp_cstr, copy_string, copy_int);

    char key1[] = "key1";
    int value1 = 10;
    hashmap_insert_copy(&map, key1, &value1);

    char key2[] = "key2";
    int value2 = 20;
    hashmap_insert_copy(&map, key2, &value2);

    delete_hashmap(&map);
    assert(map.buckets == NULL);
    assert(map.capacity == 0);
    assert(map.size == 0);

    printf("test_hashmap_delete passed!\n");
}

void test_hashmap_rehash() {
    HashMap map = create_hashmap(2, hash_cstr, cmp_cstr, copy_string, copy_int);

    // Inserir mais elementos do que a capacidade inicial para forçar o rehash
    char key1[] = "key1";
    int value1 = 10;
    hashmap_insert_copy(&map, key1, &value1);

    char key2[] = "key2";
    int value2 = 20;
    hashmap_insert_copy(&map, key2, &value2);

    char key3[] = "key3";
    int value3 = 30;
    hashmap_insert_copy(&map, key3, &value3);

    assert(map.size == 3);
    assert(map.capacity > 2); // A capacidade deve ter aumentado

    delete_hashmap(&map);
    printf("test_hashmap_rehash passed!\n");
}

void hashmap_test() {
    test_create_hashmap();
    test_hashmap_insert_move();
    test_hashmap_insert_copy();
    test_hashmap_get();
    test_hashmap_collision();
    test_hashmap_delete();
    test_hashmap_rehash();
}

#endif /* HASHMAP_TEST_H */