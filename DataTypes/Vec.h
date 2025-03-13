#ifndef LINALG_H
#define LINALG_H

#include <stdint.h>
#include <stdlib.h>
#include "../global_allocator.h"
#include "../numdef.h"

#ifdef INLINE_VEC_FUNCTIONS
#define INLINE static inline
#else
#define INLINE
#endif

enum VecType {
    VT_UNDEFINED,

    // Tipos de ponto flutuante
#ifdef HAS_F32
    VT_F32,
#endif
#ifdef HAS_F64
    VT_F64,
#endif
#ifdef HAS_F128
    VT_F128,
#endif

#ifdef HAS_I8
    VT_I8,
#endif
#ifdef HAS_I16
    VT_I16,
#endif
#ifdef HAS_I32
    VT_I32,
#endif 
#ifdef HAS_I64
    VT_I64,
#endif
#ifdef HAS_I128
    VT_I128,
#endif
#ifdef HAS_U8
    VT_U8,
#endif
#ifdef HAS_U16
    VT_U16,
#endif
#ifdef HAS_U32
    VT_U32,
#endif
#ifdef HAS_U64
    VT_U64,
#endif
#ifdef HAS_U128
    VT_U128,
#endif

    VT_COUNT,
};


// `Vec` is used for built-in data types, for custom data types use `GenericVec`
typedef struct Vec {
    void *data;
    usize dim;
    enum VecType type;
} Vec;

//Use gvec_init to initialize a generic vector
typedef struct GenericVec {
    void *data;
    usize dim;
    usize data_size;
    void *(*add)(void *, void *);
    void *(*sub)(void *, void *);
    void *(*mul)(void *, void *);
    void *(*div)(void *, void *);
} GenericVec;

Vec vec_init(usize dimensions, enum VecType type);
void vec_delete(Vec *vec);
void vec_sum(Vec *res, const Vec *v1, const Vec* v2);
void vec_sub(Vec *res, const Vec *v1, const Vec* v2);

void vec_mul_scalar(Vec *res, const Vec *v1, const void *scalar);

void vec_div_scalar(Vec *res, const Vec *v1, const void *scalar);
void vec_add_scalar(Vec *res, const Vec *v1, const void *scalar);
void vec_sub_scalar(Vec *res, const Vec *v1, const void *scalar);

void vec_cross(Vec *res, const Vec *v1, const Vec *v2);

GenericVec gvec_init(
    usize dimension,
    usize data_size,
    void *(*add)(void *data1, void *data2),
    void *(*sub)(void *data1, void *data2),
    void *(*mul)(void *data1, void *data2),
    void *(*div)(void *data1, void *data2)
);
void gvec_delete(GenericVec *vec);

#endif /* LINALG_H */