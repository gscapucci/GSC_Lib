#ifndef GLOBAL_ALLOCATOR_H
#define GLOBAL_ALLOCATOR_H

#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
extern void *(*allocate)(size_t);
extern void (*deallocate)(void*);
extern void *(*reallocate)(void*, size_t);

//default function is "malloc"
static inline void set_default_allocator(void *(*allocator)(size_t)) {
    allocate = allocator;
}
//default function is "free"
static inline void set_default_dealocator(void (*deallocator)(void*)) {
    deallocate = deallocator;
}

static inline void set_default_reallocate(void *(*reallocator)(void*, size_t)) {
    reallocate = reallocator;
}

#define SET_LOCAL_ALLOCATOR(alloator) void *(*local_allocate)(size_t) = alloator;
#define SET_LOCAL_DEALOCATOR(deallocator) void *(*local_deallocate)(void*) = deallocator;
#define SET_LOCAL_REALLOCATOR(reallocator) void *(*local_reallocate)(void*, size_t) = reallocator;

#ifdef __cpluplus
}
#endif

#endif /* GLOBAL_ALLOCATOR_H*/