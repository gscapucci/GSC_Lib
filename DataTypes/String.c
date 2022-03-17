#include "String.h"

size_t get_str_lengh(String *self);
char *get_str(String *self);
char get_at_index(String *self, size_t index);
char *concatenate_cstr(String *self, char *string);
char *concatenate_string(String *self, String *string);
void set_string(String *self, String *string);
void set_cstring(String *self, char *string);
void set_at_pos(String *self, size_t index, char value);
size_t get_sizeof_string(String *self);
void print_string(String *self);
void reverse_string(String *self);

void set_functions(String *string)
{
    string->lengh = get_str_lengh;
    string->get = get_str;
    string->get_at = get_at_index;
    string->concat_cstr = concatenate_cstr;
    string->concat = concatenate_string;
    string->clear = clear_string;
    string->set = set_string;
    string->set_at = set_at_pos;
    string->set_cstr = set_cstring;
    string->sizeof_string = get_sizeof_string;
    string->print = print_string;
    string->reverse = reverse_string;
}

size_t get_str_lengh(String *self)
{
    if(self)
    {
        if(self->_str)
        {
            return strlen(self->_str);
        }
    }
    return 0;
}

char *get_str(String *self)
{
    if(self)
    {
        if(self->_str)
        {
            return self->_str;
        }
    }
    return NULL;
}

char get_at_index(String *self, size_t index)
{
    if(self)
    {
        if(self->_str)
        {
            if(index >= strlen(self->_str))
            {
                fprintf(stderr, "index out of range");
                exit(1);
            }
            return self->_str[index];
        }
    }
    return 0;
}

char *concatenate_cstr(String *self, char *string)
{
    if(self)
    {
        if(!self->_str)
        {
            self->_str = (char *)malloc(strlen(string));
            self->_str = strcpy(self->_str, string);
        }
        else
        {
            self->_str = strcat(self->_str, string);
        }
        return self->_str;
    }
    return NULL;
}

char *concatenate_string(String *self, String *string)
{
    if(self)
    {
        if(!self->_str)
        {
            self->_str = (char *)malloc(strlen(string->_str));
            self->_str = strcpy(self->_str, string->_str);
        }
        else
        {
            self->_str = strcat(self->_str, string->_str);
        }
        return self->_str;
    }
    return NULL;
}


void set_string(String *self, String *string)
{
    self->clear(self);
    self->_str = (char *)malloc(strlen(string->_str));
    self->_str = strcpy(self->_str, string->_str);
}

void set_cstring(String *self, char *string)
{
    self->clear(self);
    self->_str = (char *)malloc(strlen(string));
    self->_str = strcpy(self->_str, string);
}

void set_at_pos(String *self, size_t index, char value)
{
    if(self)
    {
        if(self->_str)
        {
            if(index >= strlen(self->_str))
            {
                fprintf(stderr, "index out of range");
                exit(1);
            }
            self->_str[index] = value;
        }
    }
}

size_t get_sizeof_string(String *self)
{
    if(self)
    {
        return sizeof(String) + self->lengh(self);
    }
    return 0;
}

void print_string(String *self)
{
    if(self)
    {
        if(self->_str)
        {
            printf("%s", self->_str);
            return;
        }
    }
    fprintf(stderr, "Error: string is empty");
}

void reverse_string(String *self)
{
    if(self)
    {
        if(self->_str)
        {
            strrev(self->_str);
            return;
        }
    }
    fprintf(stderr, "Error: string is empty");
}

String create_string()
{
    String string;
    string._str = NULL;
    set_functions(&string);
    return string;
}

String construct_string(char *str)
{
    String string;
    string._str = (char *)malloc(strlen(str));
    string._str = strcpy(string._str, str);
    set_functions(&string);
    return string;
}

void clear_string(String *str)
{
    if(str)
    {
        if(str->_str)
        {
            free(str->_str);
            str->_str = NULL;
        }
    }
}