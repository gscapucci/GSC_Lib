#ifndef STRING_TEST_H
#define STRING_TEST_H

#include "../GSC_Lib.h"
#include <assert.h>

void test_string_create() {
    String str = string_create();
    assert(str.data != NULL);
    assert(str.length == 0);
    assert(str.capacity > 0);
    string_delete(&str);
    printf("test_string_create passed!\n");
}

void test_string_create_heap() {
    String *str = string_create_heap();
    assert(str != NULL);
    assert(str->data != NULL);
    assert(str->length == 0);
    assert(str->capacity > 0);
    string_delete_heap(str);
    printf("test_string_create_heap passed!\n");
}

void test_string_construct_by_copy() {
    const char *cstr = "Hello";
    String str = string_construct_by_copy(cstr);
    assert(str.length == strlen(cstr));
    assert(str.capacity >= str.length);
    assert(strcmp(str.data, cstr) == 0);
    string_delete(&str);
    printf("test_string_construct_by_copy passed!\n");
} 

void test_string_construct_by_copy_heap() {
    const char *cstr = "Hello";
    String *str = string_construct_by_copy_heap(cstr);
    assert(str != NULL);
    assert(str->length == strlen(cstr));
    assert(str->capacity >= str->length);
    assert(strcmp(str->data, cstr) == 0);
    string_delete_heap(str);
    printf("test_string_construct_by_copy_heap passed!\n");
}

void test_string_construct_by_move() {
    char *cstr = strdup("Hello");
    String str = string_construct_by_move(cstr);
    assert(str.length == strlen("Hello"));
    assert(str.capacity >= str.length);
    assert(strcmp(str.data, "Hello") == 0);
    string_delete(&str);
    printf("test_string_construct_by_move passed!\n");
}

void test_string_construct_by_move_heap() {
    char *cstr = strdup("Hello");
    String *str = string_construct_by_move_heap(cstr);
    assert(str != NULL);
    assert(str->length == strlen("Hello"));
    assert(str->capacity >= str->length);
    assert(strcmp(str->data, "Hello") == 0);
    string_delete_heap(str);
    printf("test_string_construct_by_move_heap passed!\n");
}

void test_string_copy() {
    String original = string_construct_by_copy("Hello");
    String copy = string_copy(&original);
    assert(copy.length == original.length);
    assert(copy.capacity >= copy.length);
    assert(strcmp(copy.data, original.data) == 0);
    string_delete(&original);
    string_delete(&copy);
    printf("test_string_copy passed!\n");
}

void test_string_copy_heap() {
    String *original = string_construct_by_copy_heap("Hello");
    String *copy = string_copy_heap(original);
    assert(copy != NULL);
    assert(copy->length == original->length);
    assert(copy->capacity >= copy->length);
    assert(strcmp(copy->data, original->data) == 0);
    string_delete_heap(original);
    string_delete_heap(copy);
    printf("test_string_copy_heap passed!\n");
}

void test_string_delete() {
    String str = string_construct_by_copy("Hello");
    string_delete(&str);
    assert(str.data == NULL);
    assert(str.length == 0);
    assert(str.capacity == 0);
    printf("test_string_delete passed!\n");
}

void test_string_delete_heap() {
    String *str = string_construct_by_copy_heap("Hello");
    string_delete_heap(str);
    // Não podemos verificar str->data diretamente após free, mas o teste não deve falhar.
    printf("test_string_delete_heap passed!\n");
}

void test_string_reverse() {
    String str = string_construct_by_copy("Hello");
    string_reverse(&str);
    assert(strcmp(str.data, "olleH") == 0);
    string_delete(&str);
    printf("test_string_reverse passed!\n");
}

void test_string_as_cstr() {
    String str = string_construct_by_copy("Hello");
    const char *cstr = string_as_cstr(&str);
    assert(strcmp(cstr, "Hello") == 0);
    string_delete(&str);
    printf("test_string_as_cstr passed!\n");
}

void test_string_starts_with() {
    String str = string_construct_by_copy("Hello, World!");
    String prefix = string_construct_by_copy("Hello");
    assert(string_starts_with(&str, &prefix));
    string_delete(&str);
    string_delete(&prefix);
    printf("test_string_starts_with passed!\n");
}

void test_string_starts_with_cstr() {
    String str = string_construct_by_copy("Hello, World!");
    assert(string_starts_with_cstr(&str, "Hello"));
    string_delete(&str);
    printf("test_string_starts_with_cstr passed!\n");
}

void test_string_ends_with() {
    String str = string_construct_by_copy("Hello, World!");
    String suffix = string_construct_by_copy("World!");
    assert(string_ends_with(&str, &suffix));
    string_delete(&str);
    string_delete(&suffix);
    printf("test_string_ends_with passed!\n");
}

void test_string_ends_with_cstr() {
    String str = string_construct_by_copy("Hello, World!");
    assert(string_ends_with_cstr(&str, "World!"));
    string_delete(&str);
    printf("test_string_ends_with_cstr passed!\n");
}

void test_string_compare() {
    String str1 = string_construct_by_copy("Hello");
    String str2 = string_construct_by_copy("Hello");
    assert(string_compare(&str1, str2) == 0);
    string_delete(&str1);
    string_delete(&str2);
    printf("test_string_compare passed!\n");
}

void test_string_compare_cstr() {
    String str = string_construct_by_copy("Hello");
    assert(string_compare_cstr(&str, "Hello") == 0);
    string_delete(&str);
    printf("test_string_compare_cstr passed!\n");
}

void test_string_find() {
    String str = string_construct_by_copy("Hello, World!");
    String substr = string_construct_by_copy("World");
    assert(string_find(&str, &substr) == 7);
    string_delete(&str);
    string_delete(&substr);
    printf("test_string_find passed!\n");
}

void test_string_find_cstr() {
    String str = string_construct_by_copy("Hello, World!");
    assert(string_find_cstr(&str, "World") == 7);
    string_delete(&str);
    printf("test_string_find_cstr passed!\n");
}

void test_string_at() {
    String str = string_construct_by_copy("Hello");
    assert(string_at(&str, 0) == 'H');
    assert(string_at(&str, 4) == 'o');
    string_delete(&str);
    printf("test_string_at passed!\n");
}

void test_string_concat() {
    String str1 = string_construct_by_copy("Hello");
    String str2 = string_construct_by_copy(", World!");
    string_concat(&str1, &str2);
    assert(strcmp(str1.data, "Hello, World!") == 0);
    string_delete(&str1);
    string_delete(&str2);
    printf("test_string_concat passed!\n");
}

void test_string_concat_cstr() {
    String str = string_construct_by_copy("Hello");
    string_concat_cstr(&str, ", World!");
    assert(strcmp(str.data, "Hello, World!") == 0);
    string_delete(&str);
    printf("test_string_concat_cstr passed!\n");
}

void test_string_clear() {
    String str = string_construct_by_copy("Hello");
    string_clear(&str);
    assert(str.length == 0);
    assert(strcmp(str.data, "") == 0);
    string_delete(&str);
    printf("test_string_clear passed!\n");
}

void string_test() {
    test_string_create();
    test_string_create_heap();
    test_string_construct_by_copy();
    test_string_construct_by_copy_heap();
    test_string_construct_by_move();
    test_string_construct_by_move_heap();
    test_string_copy();
    test_string_copy_heap();
    test_string_delete();
    test_string_delete_heap();
    test_string_reverse();
    test_string_as_cstr();
    test_string_starts_with();
    test_string_starts_with_cstr();
    test_string_ends_with();
    test_string_ends_with_cstr();
    test_string_compare();
    test_string_compare_cstr();
    test_string_find();
    test_string_find_cstr();
    test_string_at();
    test_string_concat();
    test_string_concat_cstr();
    test_string_clear();
}

#endif /* STRING_TEST_H */