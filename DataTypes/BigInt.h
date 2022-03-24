#ifndef BIG_INT_H
#define BIG_INT_H

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct BigInt BigInt;

struct BigInt{
    uint8_t *_number;
    
    size_t lengh;
    bool positive;
    
    void (*Print)(BigInt *self);

    void (*Assign_bigint)(BigInt *self, BigInt *number);
    void (*Assign_int)(BigInt *self, long long number);

    int (*Compare_bigint)(BigInt *self, BigInt *number);
    int (*Compare_int)(BigInt *self, long long number);

    void (*Sum_bigint)(BigInt *self, BigInt *number);
    void (*Sub_bigint)(BigInt *self, BigInt *number); //TODO sub bigint function
    void (*Mul_bigint)(BigInt *self, BigInt *number); //TODO mul bigint function

    void (*Sum_int)(BigInt *self, long long number); //TODO: sum int function
    void (*Sub_int)(BigInt *self, long long number); //TODO: sub int function
    void (*Mul_int) (BigInt *self, long long number); //TODO: mul int function

};

BigInt create_bigint();
BigInt construct_from_int(long long number);
BigInt construct_from_bigint(BigInt *bigint);
BigInt construct_from_string(const char *number);

void clear_bigint(BigInt *bigint);

#endif /* BIG_INT_H */