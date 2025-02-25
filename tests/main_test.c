#include "vector_test.h"
#include "hashmap_test.h"
#include "string_test.h"
#include "stack_test.h"
#include "vec_test.h"

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
        exit(1);
    }
}

int main() {
    set_default_allocator(my_malloc);
    set_default_dealocator(my_free);
    vector_test();
    hashmap_test();
    stack_test();
    string_test();
    vec_test();
    printf("All tests passed!!!!\n");
    return 0;
}