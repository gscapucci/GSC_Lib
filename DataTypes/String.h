#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct String String;

struct String
{
    char *_str;
    size_t (*lengh)(String *self);
    void (*set)(String *self, String *str);
    void (*set_at)(String *self, size_t index, char value);
    void (*set_cstr)(String *self, char *cstr);
    char *(*get)(String *self);
    char (*get_at)(String *self, size_t index);
    char *(*concat_cstr)(String *self, char *cstr);
    char *(*concat)(String *self, String *str);
    void (*print)(String *self);
    void (*clear)(String *self);
    size_t (*sizeof_string)(String *self);
    void (*reverse)(String *self);//TODO: reverse function
};



String create_string();
String construct_string(char *str);
void clear_string(String *str);

#endif /* STRING_H */