#include "Vec.h"
#include "stdbool.h"
const usize vt_to_size[VT_COUNT] = {
    [VT_UNDEFINED] = 0,
#ifndef HAS_F32
    [VT_F32] = sizeof(f32),
#endif
#ifndef HAS_F64
    [VT_F64] = sizeof(f64),
#endif
#ifndef HAS_F128
    [VT_F128] = sizeof(f128),
#endif
#ifndef HAS_I8
    [VT_I8] = sizeof(i8),
#endif
#ifndef HAS_I16
    [VT_I16] = sizeof(i16),
#endif
#ifndef HAS_I32
    [VT_I32] = sizeof(i32),
#endif
#ifndef HAS_I64
    [VT_I64] = sizeof(i64),
#endif
#ifndef HAS_I128
    [VT_I128] = sizeof(i128),
#endif
#ifndef HAS_U8
    [VT_U8] = sizeof(u8),
#endif
#ifndef HAS_U16
    [VT_U16] = sizeof(u16),
#endif
#ifndef HAS_U32
    [VT_U32] = sizeof(u32),
#endif
#ifndef HAS_U64
    [VT_U64] = sizeof(u64),
#endif
#ifndef HAS_U128
    [VT_U128] = sizeof(u128),
#endif
};

#define VEC_OPERATION(op, res, v1, v2, type) \
    type* r = (type*)res->data; \
    type* a = (type*)v1->data; \
    type* b = (type*)v2->data; \
    for (usize i = 0; i < res->dim; i++) { \
        r[i] = a[i] op b[i]; \
    }

#define VEC_SCALAR_OPERATION(op, res, v1, scalar, type) \
    type* r = (type*)res->data; \
    type* a = (type*)v1->data; \
    type scale = *(type*)scalar; \
    for (usize i = 0; i < res->dim; i++) { \
        r[i] = a[i] op scale; \
    }

inline bool is_valid_vec_type(enum VecType type) {
    return type >= 0 && type < VT_COUNT;
}


Vec vec_init(usize dimensions, enum VecType type) {
    Vec vec = {0};
    vec.dim = dimensions;
    if (!is_valid_vec_type(type)) {
        fprintf(stderr, "Error: invalid vector type.\n");
        exit(1);
    }
    u64 data_size = vt_to_size[type];
    if(data_size == 0) {
        fprintf(stderr, "Erro: Undefined vec type\n");
        exit(1);
    }
    vec.data = allocate(vec.dim * data_size);
    vec.type = type;
    return vec;
}


void vec_delete(Vec *vec) {
    if(!vec || !vec->data) return;
    deallocate(vec->data);
    vec->data = NULL;
    vec->dim = 0;
    vec->type = VT_UNDEFINED;
}



void vec_sum(Vec *res, const Vec *v1, const Vec* v2) {
    if(!res || !v1 || !v2) return;
    if (v1->dim != v2->dim || v1->dim != res->dim || v1->type != v2->type || v1->type != res->type) {
        fprintf(stderr, "Erro: Vetores com dimensões ou tipos incompatíveis.\n");
        return;
    }
    switch (res->type) {
#ifdef HAS_I8
        case VT_I8:   VEC_OPERATION(+, res, v1, v2, i8); break;
#endif
#ifdef HAS_U8
        case VT_U8:   VEC_OPERATION(+, res, v1, v2, u8); break;
#endif
#ifdef HAS_I16
        case VT_I16:  VEC_OPERATION(+, res, v1, v2, i16); break;
#endif
#ifdef HAS_U16
        case VT_U16:  VEC_OPERATION(+, res, v1, v2, u16); break;
#endif
#ifdef HAS_F32
        case VT_F32:  VEC_OPERATION(+, res, v1, v2, f32); break;
#endif
#ifdef HAS_I32
        case VT_I32:  VEC_OPERATION(+, res, v1, v2, i32); break;
#endif
#ifdef HAS_U32
        case VT_U32:  VEC_OPERATION(+, res, v1, v2, u32); break;
#endif
#ifdef HAS_F64
        case VT_F64:  VEC_OPERATION(+, res, v1, v2, f64); break;
#endif
#ifdef HAS_I64
        case VT_I64:  VEC_OPERATION(+, res, v1, v2, i64); break;
#endif
#ifdef HAS_U64
        case VT_U64:  VEC_OPERATION(+, res, v1, v2, u64); break;
#endif
#ifdef HAS_F128
        case VT_F128: VEC_OPERATION(+, res, v1, v2, f128); break;
#endif
#ifdef HAS_I128
        case VT_I128: VEC_OPERATION(+, res, v1, v2, i128); break;
#endif
#ifdef HAS_U128
        case VT_U128: VEC_OPERATION(+, res, v1, v2, u128); break;
#endif
        default:
            fprintf(stderr, "Erro: Tipo de dados não suportado.\n");
            break;
    }
}
void vec_sub(Vec *res, const Vec *v1, const Vec* v2) {
    if(!res || !v1 || !v2) return;
    if (v1->dim != v2->dim || v1->dim != res->dim || v1->type != v2->type || v1->type != res->type) {
        fprintf(stderr, "Erro: Vetores com dimensões ou tipos incompatíveis.\n");
        return;
    }
    switch (res->type) {
#ifdef HAS_I8
        case VT_I8:   VEC_OPERATION(+, res, v1, v2, i8); break;
#endif
#ifdef HAS_U8
        case VT_U8:   VEC_OPERATION(+, res, v1, v2, u8); break;
#endif
#ifdef HAS_I16
        case VT_I16:  VEC_OPERATION(+, res, v1, v2, i16); break;
#endif
#ifdef HAS_U16
        case VT_U16:  VEC_OPERATION(+, res, v1, v2, u16); break;
#endif
#ifdef HAS_F32
        case VT_F32:  VEC_OPERATION(+, res, v1, v2, f32); break;
#endif
#ifdef HAS_I32
        case VT_I32:  VEC_OPERATION(+, res, v1, v2, i32); break;
#endif
#ifdef HAS_U32
        case VT_U32:  VEC_OPERATION(+, res, v1, v2, u32); break;
#endif
#ifdef HAS_F64
        case VT_F64:  VEC_OPERATION(+, res, v1, v2, f64); break;
#endif
#ifdef HAS_I64
        case VT_I64:  VEC_OPERATION(+, res, v1, v2, i64); break;
#endif
#ifdef HAS_U64
        case VT_U64:  VEC_OPERATION(+, res, v1, v2, u64); break;
#endif
#ifdef HAS_F128
        case VT_F128: VEC_OPERATION(+, res, v1, v2, f128); break;
#endif
#ifdef HAS_I128
        case VT_I128: VEC_OPERATION(+, res, v1, v2, i128); break;
#endif
#ifdef HAS_U128
        case VT_U128: VEC_OPERATION(+, res, v1, v2, u128); break;
#endif
        default:
            fprintf(stderr, "Erro: Tipo de dados não suportado.\n");
            break;
    }
}


void vec_mul_scalar(Vec *res, const Vec *v1, const void *scalar) {
    if (!res || !v1 || !scalar) return;
    if (v1->dim != res->dim || v1->type != res->type) {
        fprintf(stderr, "Erro: Vetores com dimensões ou tipos incompatíveis.\n");
        return;
    }

    switch (res->type) {
#ifdef HAS_I8
        case VT_I8:   VEC_SCALAR_OPERATION(*, res, v1, scalar, i8); break;
#endif
#ifdef HAS_U8
        case VT_U8:   VEC_SCALAR_OPERATION(*, res, v1, scalar, u8); break;
#endif
#ifdef HAS_I16
        case VT_I16:  VEC_SCALAR_OPERATION(*, res, v1, scalar, i16); break;
#endif
#ifdef HAS_U16
        case VT_U16:  VEC_SCALAR_OPERATION(*, res, v1, scalar, u16); break;
#endif
#ifdef HAS_F32
        case VT_F32:  VEC_SCALAR_OPERATION(*, res, v1, scalar, f32); break;
#endif
#ifdef HAS_I32
        case VT_I32:  VEC_SCALAR_OPERATION(*, res, v1, scalar, i32); break;
#endif
#ifdef HAS_U32
        case VT_U32:  VEC_SCALAR_OPERATION(*, res, v1, scalar, u32); break;
#endif
#ifdef HAS_F64
        case VT_F64:  VEC_SCALAR_OPERATION(*, res, v1, scalar, f64); break;
#endif
#ifdef HAS_I64
        case VT_I64:  VEC_SCALAR_OPERATION(*, res, v1, scalar, i64); break;
#endif
#ifdef HAS_U64
        case VT_U64:  VEC_SCALAR_OPERATION(*, res, v1, scalar, u64); break;
#endif
#ifdef HAS_F128
        case VT_F128: VEC_SCALAR_OPERATION(*, res, v1, scalar, f128); break;
#endif
#ifdef HAS_I128
        case VT_I128: VEC_SCALAR_OPERATION(*, res, v1, scalar, i128); break;
#endif
#ifdef HAS_U128
        case VT_U128: VEC_SCALAR_OPERATION(*, res, v1, scalar, u128); break;
#endif
        default:
            fprintf(stderr, "Erro: Tipo de dados não suportado.\n");
            break;
    }
}

void vec_div_scalar(Vec *res, const Vec *v1, const void *scalar) {
    if (!res || !v1 || !scalar) return;
    if (v1->dim != res->dim || v1->type != res->type) {
        fprintf(stderr, "Erro: Vetores com dimensões ou tipos incompatíveis.\n");
        return;
    }

    switch (res->type) {
#ifdef HAS_I8
        case VT_I8:   VEC_SCALAR_OPERATION(/, res, v1, scalar, i8); break;
#endif
#ifdef HAS_U8
        case VT_U8:   VEC_SCALAR_OPERATION(/, res, v1, scalar, u8); break;
#endif
#ifdef HAS_I16
        case VT_I16:  VEC_SCALAR_OPERATION(/, res, v1, scalar, i16); break;
#endif
#ifdef HAS_U16
        case VT_U16:  VEC_SCALAR_OPERATION(/, res, v1, scalar, u16); break;
#endif
#ifdef HAS_F32
        case VT_F32:  VEC_SCALAR_OPERATION(/, res, v1, scalar, f32); break;
#endif
#ifdef HAS_I32
        case VT_I32:  VEC_SCALAR_OPERATION(/, res, v1, scalar, i32); break;
#endif
#ifdef HAS_U32
        case VT_U32:  VEC_SCALAR_OPERATION(/, res, v1, scalar, u32); break;
#endif
#ifdef HAS_F64
        case VT_F64:  VEC_SCALAR_OPERATION(/, res, v1, scalar, f64); break;
#endif
#ifdef HAS_I64
        case VT_I64:  VEC_SCALAR_OPERATION(/, res, v1, scalar, i64); break;
#endif
#ifdef HAS_U64
        case VT_U64:  VEC_SCALAR_OPERATION(/, res, v1, scalar, u64); break;
#endif
#ifdef HAS_F128
        case VT_F128: VEC_SCALAR_OPERATION(/, res, v1, scalar, f128); break;
#endif
#ifdef HAS_I128
        case VT_I128: VEC_SCALAR_OPERATION(/, res, v1, scalar, i128); break;
#endif
#ifdef HAS_U128
        case VT_U128: VEC_SCALAR_OPERATION(/, res, v1, scalar, u128); break;
#endif
        default:
            fprintf(stderr, "Erro: Tipo de dados não suportado.\n");
            break;
    }
}
void vec_add_scalar(Vec *res, const Vec *v1, const void *scalar) {
    if (!res || !v1 || !scalar) return;
    if (v1->dim != res->dim || v1->type != res->type) {
        fprintf(stderr, "Erro: Vetores com dimensões ou tipos incompatíveis.\n");
        return;
    }

    switch (res->type) {
#ifdef HAS_I8
        case VT_I8:   VEC_SCALAR_OPERATION(+, res, v1, scalar, i8); break;
#endif
#ifdef HAS_U8
        case VT_U8:   VEC_SCALAR_OPERATION(+, res, v1, scalar, u8); break;
#endif
#ifdef HAS_I16
        case VT_I16:  VEC_SCALAR_OPERATION(+, res, v1, scalar, i16); break;
#endif
#ifdef HAS_U16
        case VT_U16:  VEC_SCALAR_OPERATION(+, res, v1, scalar, u16); break;
#endif
#ifdef HAS_F32
        case VT_F32:  VEC_SCALAR_OPERATION(+, res, v1, scalar, f32); break;
#endif
#ifdef HAS_I32
        case VT_I32:  VEC_SCALAR_OPERATION(+, res, v1, scalar, i32); break;
#endif
#ifdef HAS_U32
        case VT_U32:  VEC_SCALAR_OPERATION(+, res, v1, scalar, u32); break;
#endif
#ifdef HAS_F64
        case VT_F64:  VEC_SCALAR_OPERATION(+, res, v1, scalar, f64); break;
#endif
#ifdef HAS_I64
        case VT_I64:  VEC_SCALAR_OPERATION(+, res, v1, scalar, i64); break;
#endif
#ifdef HAS_U64
        case VT_U64:  VEC_SCALAR_OPERATION(+, res, v1, scalar, u64); break;
#endif
#ifdef HAS_F128
        case VT_F128: VEC_SCALAR_OPERATION(+, res, v1, scalar, f128); break;
#endif
#ifdef HAS_I128
        case VT_I128: VEC_SCALAR_OPERATION(+, res, v1, scalar, i128); break;
#endif
#ifdef HAS_U128
        case VT_U128: VEC_SCALAR_OPERATION(+, res, v1, scalar, u128); break;
#endif
        default:
            fprintf(stderr, "Erro: Tipo de dados não suportado.\n");
            break;
    }
}

void vec_sub_scalar(Vec *res, const Vec *v1, const void *scalar) {
    if (!res || !v1 || !scalar) return;
    if (v1->dim != res->dim || v1->type != res->type) {
        fprintf(stderr, "Erro: Vetores com dimensões ou tipos incompatíveis.\n");
        return;
    }

    switch (res->type) {
#ifdef HAS_I8
        case VT_I8:   VEC_SCALAR_OPERATION(-, res, v1, scalar, i8); break;
#endif
#ifdef HAS_U8
        case VT_U8:   VEC_SCALAR_OPERATION(-, res, v1, scalar, u8); break;
#endif
#ifdef HAS_I16
        case VT_I16:  VEC_SCALAR_OPERATION(-, res, v1, scalar, i16); break;
#endif
#ifdef HAS_U16
        case VT_U16:  VEC_SCALAR_OPERATION(-, res, v1, scalar, u16); break;
#endif
#ifdef HAS_F32
        case VT_F32:  VEC_SCALAR_OPERATION(-, res, v1, scalar, f32); break;
#endif
#ifdef HAS_I32
        case VT_I32:  VEC_SCALAR_OPERATION(-, res, v1, scalar, i32); break;
#endif
#ifdef HAS_U32
        case VT_U32:  VEC_SCALAR_OPERATION(-, res, v1, scalar, u32); break;
#endif
#ifdef HAS_F64
        case VT_F64:  VEC_SCALAR_OPERATION(-, res, v1, scalar, f64); break;
#endif
#ifdef HAS_I64
        case VT_I64:  VEC_SCALAR_OPERATION(-, res, v1, scalar, i64); break;
#endif
#ifdef HAS_U64
        case VT_U64:  VEC_SCALAR_OPERATION(-, res, v1, scalar, u64); break;
#endif
#ifdef HAS_F128
        case VT_F128: VEC_SCALAR_OPERATION(-, res, v1, scalar, f128); break;
#endif
#ifdef HAS_I128
        case VT_I128: VEC_SCALAR_OPERATION(-, res, v1, scalar, i128); break;
#endif
#ifdef HAS_U128
        case VT_U128: VEC_SCALAR_OPERATION(-, res, v1, scalar, u128); break;
#endif
        default:
            fprintf(stderr, "Erro: Tipo de dados não suportado.\n");
            break;
    }
}

GenericVec gvec_init(
    usize dimension,
    usize data_size,
    void *(*add)(void *data1, void *data2),
    void *(*sub)(void *data1, void *data2),
    void *(*mul)(void *data1, void *data2),
    void *(*div)(void *data1, void *data2)
) {
    GenericVec vec;
    vec.dim = dimension;
    vec.data_size = data_size;
    vec.data = allocate(dimension * data_size);
    vec.add = add;
    vec.sub = sub;
    vec.mul = mul;
    vec.div = div;
    return vec;
}

void gvec_delete(GenericVec *vec) {
    if(!vec || !vec->data) return;
    deallocate(vec->data);
    vec->data = NULL;
    vec->data_size = 0;
    vec->dim = 0;
    vec->add = NULL;
    vec->sub = NULL;
    vec->mul = NULL;
    vec->div = NULL;
}