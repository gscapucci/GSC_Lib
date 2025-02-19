#include "vector_test.h"
#include "hashmap_test.h"
#include "string_test.h"
#include "stack_test.h"


int main() {
    vector_test();
    hashmap_test();
    string_test();
    stack_test();
    printf("All tests passed!!!!\n");
    return 0;
}