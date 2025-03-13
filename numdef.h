#ifndef NUMDEF_H
#define NUMDEF_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>
#include <quadmath.h>
#include <math.h>

// Verifica suporte a IEEE 754 para float (32 bits)
#if defined(__STDC_IEC_559__) || defined(__FLT32_MANT_DIG__)
    #define HAS_F32
    typedef float f32;
    #define PRIf32 "f"
    #define F32_MAX __FLT32_MAX__
    #define F32_MIN __FLT32_MIN__
#else
    #error "IEEE 754 (float 32-bit) não suportado. f32 não será definido."
#endif

// Verifica suporte a IEEE 754 para double (64 bits)
#if defined(__STDC_IEC_559__) || defined(__FLT64_MANT_DIG__)
    #define HAS_F64
    typedef double f64;
    #define PRIf64 "lf"
    #define F64_MAX __FLT64_MAX__
    #define F64_MIN __FLT64_MIN__
#else
    #error "IEEE 754 (double 64-bit) não suportado. f64 não será definido."
#endif

// Verifica suporte a long double (80 bits ou 128 bits)
#if __LDBL_MANT_DIG__ == 64 // x86 extended precision (80 bits)
    #define HAS_F80
    typedef long double f80;
    #define F80_MAX __LDBL_MAX__
    #define F80_MIN __LDBL_MIN__
    #define PRIf80 "Lf"
#elif __LDBL_MANT_DIG__ == 113 // IEEE quad-precision (128 bits)
    #define HAS_F128
    typedef long double f128;
    #define PRIf128 "Lf"
    #define F128_MAX __LDBL_MAX__
    #define F128_MIN __LDBL_MIN__
#endif

// Verifica suporte a __float128 (128 bits)
#ifndef HAS_F128
    #if defined(__SIZEOF_FLOAT128__)
        #define HAS_F128
        #include <quadmath.h>
        typedef __float128 f128;
        #define PRIf128 "Qe"
        #define F128_MAX __FLT128_MAX__
        #define F128_MIN __FLT128_MIN__
    #endif
#endif

#ifdef HAS_F128
    static inline int f128_to_str(char *buffer, size_t buffer_size, size_t num_digits_to_print, f128 num) {
        if (num_digits_to_print > 34) {
            num_digits_to_print = 34;
        }
        return quadmath_snprintf(buffer, buffer_size, "%+.34Qe", num);
    }

    static inline int print_f128(f128 num) {
        char buf[128] = {0};
        if (f128_to_str(buf, sizeof(buf), 34, num) < 0) {
            return -1;
        }
        return printf("%s", buf);
    }
#endif

// Tipos inteiros padrão
#define HAS_I8
typedef int8_t i8;
#define HAS_I16
typedef int16_t i16;
#define HAS_I32
typedef int32_t i32;
#define HAS_I64
typedef int64_t i64;


#define HAS_U8
typedef uint8_t u8;
#define HAS_U16
typedef uint16_t u16;
#define HAS_U32
typedef uint32_t u32;
#define HAS_U64
typedef uint64_t u64;

#define HAS_USIZE
typedef uintptr_t usize;
#define HAS_ISIZE
typedef intptr_t isize;

// Tipos de 128 bits
#if defined(__SIZEOF_INT128__)
    #define HAS_I128
    #define HAS_U128
    typedef __int128 i128;
    typedef unsigned __int128 u128;

    static inline i128 INT128_MAX() { return ~((i128)1 << 127); }
    static inline i128 INT128_MIN() { return ((i128)1 << 127); }
    static inline u128 UINT128_MAX() { return (u128)-1; }
    static inline u128 UINT128_MIN() { return ((u128)0); }

    static inline int u128_to_str(char *buffer, u128 num) {
        if (num == 0) {
            buffer[0] = '0';
            buffer[1] = '\0';
            return 1;
        }
        char temp[40];
        int index = 0;
        while (num > 0) {
            temp[index++] = '0' + (num % 10);
            num /= 10;
        }
        for (int i = 0; i < index; i++) {
            buffer[i] = temp[index - 1 - i];
        }
        buffer[index] = '\0';
        return index;
    }

    static inline int print_u128(u128 num) {
        char buffer[40];
        u128_to_str(buffer, num);
        return printf("%s", buffer);
    }

    static inline int i128_to_str(char *buffer, i128 num) {
        if (num == 0) {
            buffer[0] = '0';
            buffer[1] = '\0';
            return 1;
        }
    
        if (num == INT128_MIN()) {
            // Trata o caso especial de INT128_MIN separadamente, pois -INT128_MIN() causa overflow
            strcpy(buffer, "-170141183460469231731687303715884105728");
            return strlen(buffer);
        }
    
        char temp[40]; // i128 tem no máximo 39 dígitos decimais + sinal
        int index = 0;
        int is_negative = 0;
    
        // Verifica se o número é negativo
        if (num < 0) {
            is_negative = 1;
            num = -num; // Converte para positivo
        }
    
        // Converte o número para string (ordem reversa)
        while (num > 0) {
            temp[index++] = '0' + (num % 10);
            num /= 10;
        }
    
        // Adiciona o sinal negativo, se necessário
        if (is_negative) {
            temp[index++] = '-';
        }
    
        // Inverte a string para obter a ordem correta
        for (int i = 0; i < index / 2; i++) {
            char c = temp[i];
            temp[i] = temp[index - 1 - i];
            temp[index - 1 - i] = c;
        }
        temp[index] = '\0'; // Adiciona o terminador nulo
    
        // Copia o resultado para o buffer de saída
        strcpy(buffer, temp);
    
        return index;
    }
    

    static inline int print_i128(i128 num) {
        char buffer[40];
        i128_to_str(buffer, num);
        return printf("%s", buffer);
    }

#else
    #warning "Inteiros de 128 bits não suportados."
#endif

#endif /* NUMDEF_H */
