#include "BigInt.h"

void print_bigint(BigInt *self)
{
    if(!self->positive)
    {
        printf("-");
    }
    printf("%s\n", self->number);
}

BigInt *create_bigint()
{
    BigInt *new_bigint = (BigInt *)malloc(sizeof(BigInt));
    if(new_bigint)
    {
        new_bigint->number = NULL;
        new_bigint->number_lengh = 0;
        new_bigint->positive = true;
        new_bigint->print = print_bigint;
        return new_bigint;
    }
    return NULL;
}
BigInt *construct(long long number)
{
    BigInt *new_bigint = (BigInt *)malloc(sizeof(BigInt));
    if(new_bigint)
    {
        if(number < 0)
        {
            new_bigint->positive = false;
            number *= -1;
        }
        else
        {
            new_bigint->positive = true;
        }
        new_bigint->number_lengh = floor(log10(number)) + 1;
        new_bigint->number = (char *)malloc(new_bigint->number_lengh * sizeof(char));
        sprintf((char *)new_bigint->number, "%lld", number);
        new_bigint->print = print_bigint;
        return new_bigint;
    }
    return NULL;
}

BigInt *construct_from_bigint(BigInt *bigint)
{
    BigInt *new_bigint = (BigInt *)malloc(sizeof(BigInt));
    if(new_bigint)
    {
        new_bigint->print = print_bigint;
        new_bigint->number_lengh = bigint->number_lengh;
        new_bigint->positive = bigint->positive;
        new_bigint->number = (char *)malloc(bigint->number_lengh * sizeof(char));
        strcpy((char *)new_bigint->number, (char *)bigint->number);
        return new_bigint;
    }
    return NULL;
}   

void free_big_int(BigInt *bigint)
{
    if(bigint)
    {
        if(bigint->number)
        {
            free(bigint->number);
        }
    }
}