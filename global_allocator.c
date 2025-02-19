#include "global_allocator.h"

void *(*allocate)(size_t) = malloc;
void (*deallocate)(void*) = free;
void *(*reallocate)(void*, size_t) = realloc;