#include "Vec.h"

Vec vec_init(usize dimensions, enum VecType type) {
    Vec vec = {0};
    vec.dim = dimensions;
    u64 data_size = 0;
    switch(type) {
        case VT_I8:
        case VT_U8:
            data_size = sizeof(i8);
            break;
        case VT_I16:
        case VT_U16:
            data_size = sizeof(i16);
            break;
        case VT_F32:
        case VT_I32:
        case VT_U32:
            data_size = sizeof(i32);
            break;
        case VT_F64:
        case VT_I64:
        case VT_U64:
            data_size = sizeof(i64);
            break;
        case VT_F128:
        case VT_I128:
        case VT_U128:
            data_size = sizeof(i128);
            break;
        case VT_UNDEFINED:
        default:
        fprintf(stderr, "Undefined data type\n");
            break;
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



void vec_sum(Vec *res, Vec *v1, Vec* v2) {
    if(!res || !v1 || !v2) return;
    if (v1->dim != v2->dim || v1->dim != res->dim || v1->type != v2->type || v1->type != res->type) {
        fprintf(stderr, "Erro: Vetores com dimensões ou tipos incompatíveis.\n");
        return;
    }
    #define SUM(type, res, v1, v2, index) \
        type* r =  (type*)res->data;\
        type* a = (type*)v1->data;\
        type* b = (type*)v2->data;\
        r[index] = a[index] + b[index];
    for(usize i = 0; i < v1->dim; i++) {

        switch (res->type) {
            case VT_I8: {
                SUM(i8, res, v1, v2, i);
                break;
            }
            case VT_U8: {
                SUM(u8, res, v1, v2, i);
                break;
            }
            case VT_I16: {
                SUM(i16, res, v1, v2, i);
                break;
            }
            case VT_U16: {
                SUM(u16, res, v1, v2, i);
                break;
            }
            case VT_F32: {
                SUM(f32, res, v1, v2, i);
                break;
            }
            case VT_I32: {
                SUM(i32, res, v1, v2, i);
                break;
            }
            case VT_U32: {
                SUM(u32, res, v1, v2, i);
                break;
            }
            case VT_F64: {
                SUM(f64, res, v1, v2, i);
                break;
            }
            case VT_I64: {
                SUM(i64, res, v1, v2, i);
                break;
            }
            case VT_U64: {
                SUM(u64, res, v1, v2, i);
                break;
            }
            case VT_F128: {
                SUM(f128, res, v1, v2, i);
                break;
            }
            case VT_I128: {
                SUM(i128, res, v1, v2, i);
                break;
            }
            case VT_U128: {
                SUM(u128, res, v1, v2, i);
                break;
            }
            case VT_UNDEFINED:
            default:
                fprintf(stderr, "Erro: Tipo de dados não suportado.\n");
                break;
        }
    }
}
void vec_sub(Vec *res, Vec *v1, Vec* v2);
void vec_mul_scalar(Vec *res, Vec *v1, void *scalar);


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