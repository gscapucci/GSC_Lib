#include "bigint.h"

#define INDEX_MAX_NUMBER 9999999999999999999 //max number with only '9' digit that uint64 can hold
#define INDEX_MAX_NUMBER_LEN 19 //len(MAX(uint64)) - 1

//---------------------//
void print_index(uint64_t number);
uint64_t charptr_to_uint64_t(char *number);

void print_bigint(BigInt *bigint);
//---------------------//

void print_index(uint64_t number)
{
    uint8_t number_lengh = floor(log10(number)) + 1;
    for (size_t i = number_lengh; i < INDEX_MAX_NUMBER_LEN; i++)
    {
        printf("0");
    }
    printf("%lld", number);
}

uint64_t charptr_to_uint64_t(char *number)
{
    uint64_t number;
    for (size_t i = 0; i < count; i++)
    {
        /* code */
    }
    
    return number;
}

void print_bigint(BigInt *bigint)
{
    if(bigint)
    {
        if(bigint->number.vector == NULL)
        {
            fprintf(stderr, "invalid input vector function print");
            exit(1);
        }
        for (size_t i = bigint->last_used_index;; i--)
        {
            if(i == bigint->last_used_index)
            {
                printf("%lld", bigint->number.vector[0]);
            }
            else
            {
                print_index(bigint->number.vector[i]);
            }
            if(!i){break;}
        }
    return;
    }
    fprintf(stderr, "invalid input function print");
    exit(1);
}

BigInt create_bigint()
{
    BigInt bigint;
    bigint.number = create_uint64_vec(100);
    bigint.Print = print_bigint;
    bigint.last_used_index = 0;
    return bigint;
}

BigInt construct_from_int(int64_t number)
{
    BigInt bigint = create_bigint();
    bigint.number.Push(&bigint.number, number);
    return bigint;
}

BigInt construct_from_charptr(char *str)
{
    BigInt bigint = create_bigint();
    
    char aux[INDEX_MAX_NUMBER_LEN];
    uint64_t str_len, parts, res, next_part;

    str_len = strlen(str);
    parts = str_len / INDEX_MAX_NUMBER_LEN;
    res = str_len % INDEX_MAX_NUMBER_LEN;
    next_part = 0;
    for (size_t i = INDEX_MAX_NUMBER_LEN - 1;; i--)
    {
        aux[i] = str[str_len - 1 - (i - INDEX_MAX_NUMBER_LEN - 1) - next_part];
        printf("%c", aux[i]);
        if(!i)
        {
            bigint.number.Push(&bigint.number, charptr_to_uint64_t(aux));
            i = INDEX_MAX_NUMBER_LEN - 1;
            next_part++;
            if(next_part == parts)
            {
                break;
            }
        }
    }
    
    return bigint;
}

BigInt construct_from_BigInt(BigInt *bigint)
{
    fprintf(stderr, "construct_from_BigInt, not implemented yet");
    exit(1);
}

void clear_bigint(BigInt *bigint)
{
    if(bigint)
    {
        clear_uint64_vec(&bigint->number);
        bigint->last_used_index = 0;
        return;
    }
    fprintf(stderr, "invalid input function clear_bigint");
    exit(1);
}