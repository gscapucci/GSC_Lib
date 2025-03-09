#ifndef MATRIX_H
#define MATRIX_H

#include "../numdef.h"

enum __attribute__((packed)) MatType {
    MT_UNDEFINED,
    MT_F32,
    MT_F64,
    MT_F128,
    MT_I8,
    MT_I16,
    MT_I32,
    MT_I64,
    MT_I128,
    MT_U8,
    MT_U16,
    MT_U32,
    MT_U64,
    MT_U128,
};

typedef struct Mat {
    void *data;
    u64 col;
    u64 row;
    enum MatType type;
} Mat;

//Use gvec_init to initialize a generic vector
typedef struct GenericMat {
    void *data;
    u64 dim;
    u64 data_size;
    void *(*add)(void *, void *);
    void *(*sub)(void *, void *);
    void *(*mul)(void *, void *);
    void *(*div)(void *, void *);
} GenericVec;

#endif /* MATRIX_H */