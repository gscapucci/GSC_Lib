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
    void (*Sub_bigint)(BigInt *self, BigInt *number); //TODO: sub bigint function
    void (*Mul_bigint)(BigInt *self, BigInt *number); //TODO: mul bigint function
    void (*Div_bigint)(BigInt *self, BigInt *number); //TODO: div bigint function

    void (*Sum_int)(BigInt *self, long long number);
    void (*Sub_int)(BigInt *self, long long number); //TODO: sub int function
    void (*Mul_int)(BigInt *self, long long number); //TODO: mul int function
    void (*Div_int)(BigInt *self, long long number); //TODO: div int function

    void (*Get_copy)(BigInt *self); //TODO: this function
    int (*To_int)(); //TODO: this function
    long (*To_long)(); //TODO: this function
    long long (*To_long_long)(); //TODO: this function
    unsigned int (*To_unsigned_int)(); //TODO: this function
    unsigned long (*To_unsigned_long)(); //TODO: this function
    unsigned long long (*To_unsigned_long_long)(); //TODO: this function
    size_t (*To_size_t)(BigInt *self); //TODO: this function
    int8_t (*To_int8_t)(BigInt *self); //TODO: this function
    int16_t (*To_int16_t)(BigInt *self); //TODO: this function
    int32_t (*To_int32_t)(BigInt *self); //TODO: this function
    int64_t (*To_int64_t)(BigInt *self); //TODO: this function
    uint8_t (*To_uint8_t)(BigInt *self); //TODO: this function
    uint16_t (*To_uint16_t)(BigInt *self); //TODO: this function
    uint32_t (*To_uint32_t)(BigInt *self); //TODO: this function
    uint64_t (*To_uint64_t)(BigInt *self); //TODO: this function
};

BigInt create_bigint();
BigInt construct_from_int(long long number);
BigInt construct_from_bigint(BigInt *bigint);
BigInt construct_from_string(const char *number);

void clear_bigint(BigInt *bigint);

#endif /* BIG_INT_H */