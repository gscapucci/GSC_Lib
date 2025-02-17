#include "String.h"

#define SWAP(type, x, y) \
    do {\
        type tmp = x;\
        x = y;\
        y = tmp;\
    }while(0)
        
String create_string() {
    String string = {0};
    return string;
}
String construct_string_by_copy(const char *cstr) {
    String string;
    string.len = strlen(cstr);
    string.str = alloc(string.len + 1);
    memcpy(string.str, cstr, string.len + 1);
    return string;
}
String construct_string_by_move(char *cstr) {
    String string;
    string.len = strlen(cstr);
    string.str = cstr;
    return string;
}

void delete_string(String *string) {
    if(string && string->str) {
        dealloc(string->str);
    }
    string->str = NULL;
    string->len = 0;
}

void string_reverse(String *string) {
    const int len = strlen(string->str);
    for(int i = 0; i < len / 2; i++) {
        SWAP(char, string->str[i], string->str[len - 1 - i]);
    }
}

const char *string_as_cstr(String *string) {
    return string->str;
}