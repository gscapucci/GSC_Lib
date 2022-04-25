#include "bigint.h"

#define INDEX_MAX_NUMBER 9999999999999999999 //max number with only '9' digit that uint64 can hold
#define INDEX_MAX_NUMBER_LEN 19 //len(MAX(uint64)) - 1

//---------------------//
void print_index(uint64_t number);
uint64_t charptr_to_uint64_t(char *number);
bool is_number(char *str, size_t str_len);

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

uint64_t charptr_to_uint64_t(char *str)
{
    uint64_t number = 0;
    for (size_t i = INDEX_MAX_NUMBER_LEN - 1;; i--)
    {
        number += (uint64_t)(str[i] - '0') * (uint64_t)powl(10, INDEX_MAX_NUMBER_LEN - 1 - i);
        if(!i){break;}
    }
    return number;
}

bool is_number(char *str, size_t str_len)
{
    for (size_t i = 0; i < str_len; i++)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }
    return true;
}

void print_bigint(BigInt *bigint)
{
    if(bigint)
    {
        if(bigint->number.vector == NULL)
        {
            ERROR("invalid input vector");
        }
        for (size_t i = bigint->number.size - 1;; i--)
        {
            if(i == bigint->number.size - 1)
            {
                printf("%lld", bigint->number.vector[i]);
            }
            else
            {
                print_index(bigint->number.vector[i]);
            }
            if(!i){break;}
        }
    return;
    }
    ERROR("invalid input");
}

BigInt create_bigint()
{
    BigInt bigint;
    bigint.number = create_uint64_vec(100);
    bigint.Print = print_bigint;
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
    
    char aux[INDEX_MAX_NUMBER_LEN] = {0};
    uint64_t str_len, parts, res, next_part;

    str_len = strlen(str);
    if(!is_number(str, str_len))
    {
        ERROR("input is not a number");
    }
    parts = str_len / INDEX_MAX_NUMBER_LEN;
    res = str_len % INDEX_MAX_NUMBER_LEN;
    next_part = 0;
    if(parts > 0)
    {
        for (size_t i = INDEX_MAX_NUMBER_LEN - 1;; i--)
        {
            aux[i] = str[(str_len - 1) - ((INDEX_MAX_NUMBER_LEN - 1) - i) - next_part];
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
    }
    if(res > 0)
    {
        for (size_t i = 0; i < INDEX_MAX_NUMBER_LEN - res; i++)
        {
            aux[i] = '0';
        }
        for (size_t i = INDEX_MAX_NUMBER_LEN - res; i < INDEX_MAX_NUMBER_LEN; i++)
        {
            uint64_t pos = i - (INDEX_MAX_NUMBER_LEN - res);
            aux[i] = str[pos];
        }
        bigint.number.Push(&bigint.number, charptr_to_uint64_t(aux));
    }
    return bigint;
}

BigInt construct_from_BigInt(BigInt *bigint)
{
    if(bigint)
    {
        BigInt new_bigint = create_bigint();
        new_bigint.Print = print_bigint;
        for (size_t i = 0; i < bigint->number.size; i++)
        {
            new_bigint.number.Push(&new_bigint.number, bigint->number.vector[i]);
        }
        return new_bigint;
    }
    ERROR("invalid input");
}

void clear_bigint(BigInt *bigint)
{
    if(bigint)
    {
        clear_uint64_vec(&bigint->number);
        return;
    }
    ERROR("invalid input");
}