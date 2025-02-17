#ifndef GLOBAL_ALLOCATOR_H
#define GLOBAL_ALLOCATOR_H

#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
extern void *(*alloc)(size_t);
extern void (*dealloc)(void*);

//default function is "malloc"
static inline void set_default_allocator(void *(*allocator)(size_t)) {
    alloc = allocator;
}
//default function is "free"
static inline void set_default_dealocator(void (*deallocator)(void*)) {
    dealloc = deallocator;
}

#ifdef __cpluplus
}
#endif

#endif /* GLOBAL_ALLOCATOR_H*/