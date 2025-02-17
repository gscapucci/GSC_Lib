#include "global_allocator.h"

void *(*alloc)(size_t) = malloc;
void (*dealloc)(void*) = free;