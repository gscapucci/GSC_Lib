#ifndef STRING_H
#define STRING_H

#include "../global_allocator.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct String String;

struct String {
    char *data;
    size_t length;
    size_t capacity;
};


String string_create();
String string_construct_by_copy(const char *str);
String string_construct_by_move(char *str);
String string_copy(const String *str);

String *string_create_heap();
String *string_construct_by_copy_heap(const char *str);
String *string_construct_by_move_heap(char *str);
String *string_copy_heap(const String *str);

void string_delete(String *str);
void string_delete_heap(String *str);

void string_reverse(String *str);

const char *string_as_cstr(const String *str);

bool string_starts_with(const String *str, const String *suffix);
bool string_starts_with_cstr(const String *str, const char *suffix);
bool string_ends_with(const String *str, const String *end);
bool string_ends_with_cstr(const String *str, const char *end);

int string_compare(const String *str1, const String str2);
int string_compare_cstr(const String *str1, const char *cstr);

int string_find(const String *str, const String *substr);
int string_find_cstr(const String *str, const char *substr);

char string_at(const String *str, size_t index);

void string_concat(String *str1, const String *str2);
void string_concat_cstr(String *str, const char *cstr);

void string_clear(String *str);

#endif /* STRING_H */