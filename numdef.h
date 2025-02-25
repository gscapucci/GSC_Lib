#ifndef NUMDEF_H
#define NUMDEF_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h> // Para macros de formatação como PRId64, PRIu64, etc.
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
    #warning "IEEE 754 (float 32-bit) não suportado. f32 não será definido."
#endif

// Verifica suporte a IEEE 754 para double (64 bits)
#if defined(__STDC_IEC_559__) || defined(__FLT64_MANT_DIG__)
    #define HAS_F64
    typedef double f64;
    #define PRIf64 "lf"
    #define F64_MAX __FLT64_MAX__
    #define F64_MIN __FLT64_MIN__
#else
    #warning "IEEE 754 (double 64-bit) não suportado. f64 não será definido."
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
#else
    #warning "long double de 80 ou 128 bits não suportado. f80 não será definido."
#endif

// Verifica suporte a __float128 (128 bits)
#ifndef f128
#if defined(__SIZEOF_FLOAT128__) // GCC/Clang suportam __float128
    #define HAS_F128
    typedef __float128 f128;
    #define PRIf128 "Qe"
    #define F128_MAX __FLT128_MAX__
    #define F128_MIN __FLT128_MIN__
    #include <quadmath.h> // Para quadmath_snprintf
    // maximum is 34 digits
    static inline int f128_to_str(char *buffer, size_t buffer_size, size_t num_digits_to_print, f128 num) {
        char fmt[10] = {0};
        sprintf(fmt, "%%.%zu"PRIf128, num_digits_to_print);
        if(num_digits_to_print > 34) {
            num_digits_to_print = 34;
        }
        return quadmath_snprintf(buffer, buffer_size, fmt, num);
    }
    // maximum is 34 digits
    static inline int print_f128(f128 num, size_t num_digits) {
        if(num_digits > 34) {
            num_digits = 34;
        }
        char buf[36] = {0};
        return f128_to_str(buf, 36, num_digits, num) & printf("%s", buf);
    }
    #warning "Using quadmath for f128."
#else
    #warning "__float128 não suportado. f128 não será definido."
#endif
#endif
// Tipos inteiros padrão
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Tipos de 128 bits
#if defined(__SIZEOF_INT128__)// GCC/Clang suportam __int128
    #define HAS_I128
    #define HAS_U128
    typedef __int128 i128;
    typedef unsigned __int128 u128;

    static inline i128 INT128_MAX() {
        return ~((i128)1 << 127);
    }
    static inline i128 INT128_MIN() {
        return ((i128)1 << 127);
    }
    static inline u128 UINT128_MAX() {
        return (u128)-1;
    }
    static inline u128 UINT128_MIN() {
        return ((u128)0);
    }
    
    static inline int u128_to_str(char *buffer, u128 num) {
        if (num == 0) {
            buffer[0] = '0';
            buffer[1] = '\0';
            return 1;
        }
    
        char temp[40]; // Um u128 tem no máximo 39 dígitos decimais
        int index = 0;
    
        // Converte o número para string (em ordem reversa)
        while (num > 0) {
            temp[index++] = '0' + (num % 10);
            num /= 10;
        }
    
        // Inverte a string para obter a ordem correta
        for (int i = 0; i < index; i++) {
            buffer[i] = temp[index - 1 - i];
        }
        buffer[index] = '\0'; // Adiciona o terminador nulo
    
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
    
        char temp[40]; // Um i128 tem no máximo 39 dígitos decimais
        int index = 0;
        int is_negative = 0;
    
        // Verifica se o número é negativo
        if (num < 0) {
            is_negative = 1;
            num = -num; // Converte para positivo
        }
    
        // Converte o número para string (em ordem reversa)
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
    
    // Função para imprimir i128
    static inline int print_i128(i128 num) {
        char buffer[40];
        i128_to_str(buffer, num);
        return printf("%s", buffer);
    }

#else
    // Fallback para compiladores sem suporte a 128 bits
    #warning "Inteiros de 128 bits não suportados. i128 e u128 não serão definidos."
#endif

#endif /* NUMDEF_H */