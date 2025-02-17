#include "GSC_Lib.h"


static size_t alloc_count = 0;
void *my_malloc(size_t bytes) {
    void *ptr = malloc(bytes);
    if(!ptr) {
        fprintf(stderr, "Allocation fail.");
        exit(1);
    }
    alloc_count++;
    return ptr;
}

static size_t free_count = 0;
void my_free(void *ptr) {
    free_count++;
    free(ptr);
}

void check_mem() {
    if(alloc_count != free_count) {
        printf("\nYou have memory leak\n");
        printf("total allocations: %zu\n", alloc_count);
        printf("total dealocations: %zu\n", free_count);
    }
}


void destruct_string_defer(void *data) {
    printf("Destruiu %s\n", ((String *)data)->str);
    destruct_string((String*)data);
}

void *copy_str(void *str) {
    char *ret = alloc(strlen((char*)str) + 1);
    memcpy(ret, str, strlen((char*)str) + 1);
    return ret;
}

void *copy_int(void *num) {
    int64_t *n = alloc(sizeof(int64_t));
    *n = *(int64_t*)num;
    return n;
}

int main() {
    set_default_allocator(my_malloc);
    set_default_dealocator(my_free);
    defer(check_mem, check_mem, NULL);

    HashMap str_to_int = create_hashmap(10, hash_cstr, cmp_cstr, copy_str, copy_int);
    defer(str_to_int, delete_hashmap, &str_to_int);

    hashmap_insert_copy(&str_to_int, "Um", &(int64_t){1});
    hashmap_insert_copy(&str_to_int, "Dois", &(int64_t){2});
    hashmap_insert_copy(&str_to_int, "Tres", &(int64_t){3});

    if((*(int64_t *)hashmap_get(&str_to_int, "Um")) == 1) {
        printf("Funcionou 1\n");
    }
    if((*(int64_t *)hashmap_get(&str_to_int, "Dois")) == 2) {
        printf("Funcionou 2\n");
    }
    if((*(int64_t *)hashmap_get(&str_to_int, "Tres")) == 3) {
        printf("Funcionou 3\n");
    }
    return 0;
}