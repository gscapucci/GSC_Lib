#include "String.h"

#define SWAP(type, x, y) \
    do {\
        type tmp = x;\
        x = y;\
        y = tmp;\
    }while(0)
        

#define MIM_CAP 32
String string_create() {
    String string = {0};
    string.capacity = MIM_CAP;
    string.data = allocate(MIM_CAP);
    string.length = 0;
    return string;
}
String string_construct_by_copy(const char *cstr) {
    String string;
    string.length = strlen(cstr);
    string.capacity = string.length * 1.5;
    string.data = allocate(string.capacity);
    memcpy(string.data, cstr, string.length + 1);
    return string;
}
String string_construct_by_move(char *cstr) {
    String string;
    string.length = strlen(cstr);
    string.data = cstr;
    string.capacity = string.length * 1.5;
    string.data = reallocate(string.data, string.capacity);
    return string;
}


String string_copy(const String *str) {
    String string;
    string.capacity = str->capacity;
    string.length = str->length;
    string.data = allocate(str->capacity);
    memcpy(string.data, str->data, str->length + 1);
    return string;
}

String *string_create_heap() {
    String *new = allocate(sizeof(String));
    *new = string_create();
    return new;
}
String *string_construct_by_copy_heap(const char *str) {
    String *new = allocate(sizeof(String));
    *new = string_construct_by_copy(str);
    return new;
}
String *string_construct_by_move_heap(char *str) {
    String *new = allocate(sizeof(String));
    *new = string_construct_by_move(str);
    return new;
}
String *string_copy_heap(const String *str) {
    String *new = allocate(sizeof(String));
    *new = string_copy(str);
    return new;
}

void string_delete(String *string) {
    if(string && string->data) {
        deallocate(string->data);
    }
    string->data = NULL;
    string->capacity = 0;
    string->length = 0;
}

void string_delete_heap(String *str) {
    if(str && str->data) {
        deallocate(str->data);
        deallocate(str);
    }
    
}

void string_reverse(String *string) {
    const int length = strlen(string->data);
    for(int i = 0; i < length / 2; i++) {
        SWAP(char, string->data[i], string->data[length - 1 - i]);
    }
}

const char *string_as_cstr(const String *string) {
    return string->data;
}


bool string_ends_with(const String *data, const String *suffix) {
    // Verifica se as strings são válidas
    if (!data || !suffix) {
        return false;
    }

    // Obtém o comprimento das strings

    // Se o sufixo for maior que a string, não pode ser um sufixo
    if (suffix->length > data->length) {
        return false;
    }

    // Compara os últimos caracteres da string com o sufixo
    return strncmp(data->data + data->length - suffix->length, suffix->data, suffix->length) == 0;

}
bool string_ends_with_cstr(const String *data, const char *suffix) {
    // Verifica se as strings são válidas
    if (!data || !suffix) {
        return false;
    }

    // Obtém o comprimento das strings
    size_t suffix_len = strlen(suffix);
    // Se o sufixo for maior que a string, não pode ser um sufixo
    if (suffix_len > data->length) {
        return false;
    }

    // Compara os últimos caracteres da string com o sufixo
    return strncmp(data->data + data->length - suffix_len, suffix, suffix_len) == 0;
}


bool string_starts_with(const String *data, const String *suffix) {
    // Verifica se os ponteiros são válidos
    if (!data || !suffix || !data->data || !suffix->data) {
        return false;
    }

    // Se o sufixo for maior que a string, não pode ser um prefixo
    if (suffix->length > data->length) {
        return false;
    }

    // Compara os primeiros caracteres da string com o sufixo
    return strncmp(data->data, suffix->data, suffix->length) == 0;
}

// Função para verificar se uma String começa com um sufixo (do tipo C-string)
bool string_starts_with_cstr(const String *data, const char *suffix) {
    // Verifica se os ponteiros são válidos
    if (!data || !data->data || !suffix) {
        return false;
    }

    // Obtém o comprimento do sufixo
    size_t suffix_len = strlen(suffix);

    // Se o sufixo for maior que a string, não pode ser um prefixo
    if (suffix_len > data->length) {
        return false;
    }

    // Compara os primeiros caracteres da string com o sufixo
    return strncmp(data->data, suffix, suffix_len) == 0;
}

int string_compare(const String *str1, const String str2) {
    return strcmp(str1->data, str2.data);
}
int string_compare_cstr(const String *str1, const char *cstr) {
    return strcmp(str1->data, cstr);
}

void compute_lps(const char *substr, size_t substr_len, int *lps) {
    size_t len = 0;
    lps[0] = 0;
    for(size_t i = 0; i < substr_len;) {
        if(substr[i] == substr[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
int string_find(const String *str, const String *substr) {
    if(substr->length == 0) {
        return 0;
    }

    int *lps = (int *)allocate(substr->length * sizeof(int));
    if(!lps) {
        return -1;
    }

    compute_lps(substr->data, substr->length, lps);

    size_t i = 0;
    size_t j = 0;

    while(i < str->length) {
        if(substr->data[j] == str->data[i]) {
            i++;
            j++;
        }

        if(j == substr->length) {
            deallocate(lps);
            return (int)(i - j);
        }

        if(i < str->length && substr->data[j] != str->data[i]) {
            if(j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    deallocate(lps);
    return -1;
}
int string_find_cstr(const String *str, const char *substr) {
    size_t substr_length = strlen(substr);
    if(substr_length == 0) {
        return 0;
    }

    int *lps = (int *)allocate(substr_length * sizeof(int));
    if(!lps) {
        return -1;
    }

    compute_lps(substr, substr_length, lps);

    size_t i = 0;
    size_t j = 0;

    while(i < str->length) {
        if(substr[j] == str->data[i]) {
            i++;
            j++;
        }

        if(j == substr_length) {
            deallocate(lps);
            return (int)(i - j);
        }

        if(i < str->length && substr[j] != str->data[i]) {
            if(j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    deallocate(lps);
    return -1;
}

char string_at(const String *str, size_t index) {
    if(index >= str->length) return '\0';
    return str->data[index];
}

void string_concat(String *str1, const String *str2) {
    if(str2->length == 0) return;
    if(str1->capacity < (str1->length + str2->length) * 1.5) {
        str1->capacity = (str1->length + str2->length) * 1.5;
    }
    str1->data = reallocate(str1->data, str1->capacity);
    strcat(str1->data, str2->data);
    str1->length += str2->length;
}
void string_concat_cstr(String *str, const char *cstr) {
    size_t cstr_len = strlen(cstr);
    if(str->capacity < (str->length + cstr_len) * 1.5) {
        str->capacity = (str->length + cstr_len) * 1.5;
    }
    str->data = reallocate(str->data, str->capacity);
    strcat(str->data, cstr);
    str->length += cstr_len;
}

void string_clear(String *str) {
    if(str->capacity != 0) {
        str->data[0] = 0;
    }
    str->length = 0;
}