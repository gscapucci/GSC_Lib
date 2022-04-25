#ifndef BIGINT_H
#define BIGINT_H

#include "uint64_vector.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct BigInt BigInt;

struct BigInt
{
    Uint64_vec number;
    void (*Print)(BigInt *self);
};

BigInt create_bigint();
BigInt construct_from_int(long long number);
BigInt construct_from_charptr(char *str);
BigInt construct_from_BigInt(BigInt *bigint);

void clear_bigint(BigInt *bigint);
#endif /* BIGINT_H */