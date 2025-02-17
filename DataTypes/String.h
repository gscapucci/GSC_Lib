#ifndef STRING_H
#define STRING_H

#include "../global_allocator.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct String String;

struct String {
    char *str;
    size_t len;
};



String create_string();
String construct_string_by_copy(const char *str);
String construct_string_by_move(char *str);
void delete_string(String *str);
void string_reverse(String *str);
const char *string_as_cstr(String *str);

#endif /* STRING_H */