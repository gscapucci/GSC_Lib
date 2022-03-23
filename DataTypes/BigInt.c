#include "BigInt.h"

//--functions-definitions--//
void set_bigint_functions(BigInt *bigint);

void print_bigint(BigInt *self);
void assign_bigint_(BigInt *self, BigInt *number);
void assign_int_(BigInt *self, long long number);
int compare_bigint_to_bigint(BigInt *self, BigInt *number);
int compare_bigint_to_int(BigInt *self, long long number);
void sum_bigint(BigInt *self, BigInt *number);

//------------------------ //

void set_bigint_functions(BigInt *bigint)
{
    bigint->Print = print_bigint;
    bigint->Assign_bigint = assign_bigint_;
    bigint->Compare_bigint = compare_bigint_to_bigint;
    bigint->Compare_int = compare_bigint_to_int;
    bigint->Sum_bigint = sum_bigint;
}

void print_bigint(BigInt *self)
{
    if(!self->positive)
    {
        printf("-");
    }
    printf("%s", self->_number);
}

void assign_bigint_(BigInt *self, BigInt *number)
{
    if(self)
    {
        clear_bigint(self);
        *self = construct_from_bigint(number);
    }
}

void assign_int_(BigInt *self, long long number)
{
    if(self)
    {
        clear_bigint(self);
        *self = construct_from_int(number);
    }
}

int compare_bigint_to_bigint(BigInt *self, BigInt *number)
{
    if(self && number)
    {
        if(self->positive != number->positive || self->lengh > number->lengh)
        {
            return self->positive ? 1 : -1;
        }
        if(self->lengh < number->lengh)
        {
            return self->positive ? -1 : 1;
        }
        for (size_t i = 0; i < number->lengh; i++)
        {
            if(self->_number[i] > number->_number[i])
            {
                return 1;
            }
            if(self->_number[i] < number->_number[i])
            {
                return -1;
            }
        }
        return 0;
    }
    fprintf(stderr, "one or two inputs was not valid");
    exit(1);
    return -2;
}

int compare_bigint_to_int(BigInt *self, long long number)
{
    if(self)
    {
        BigInt aux = construct_from_int(number);
        return self->Compare_bigint(self, &aux);
    }
    fprintf(stderr, "input was not valid");
    exit(1);
    return 0;
}

void sum_bigint(BigInt *self, BigInt *number)
{
    if(self && number)
    {
        //TODO
    }
    fprintf(stderr, "invalid inputs");
    exit(1);
}

BigInt create_bigint()
{
    BigInt new_bigint;
    new_bigint._number = (char *)malloc(2 * sizeof(char));
    new_bigint._number[0] = '0';
    new_bigint._number[1] = '\0';
    new_bigint.lengh = 1;
    new_bigint.positive = true;
    set_bigint_functions(&new_bigint);
    return new_bigint;
}

BigInt construct_from_int(long long number)
{
    BigInt new_bigint;
    if(number < 0)
    {
        new_bigint.positive = false;
        number *= -1;
    }
    else
    {
        new_bigint.positive = true;
    }
    new_bigint.lengh = floor(log10(number)) + 1;
    new_bigint._number = (char *)malloc(new_bigint.lengh * sizeof(char));
    sprintf(new_bigint._number, "%lld", number);
    set_bigint_functions(&new_bigint);
    return new_bigint;
}

BigInt construct_from_bigint(BigInt *bigint)
{
    BigInt new_bigint;
    new_bigint.lengh = bigint->lengh;
    new_bigint.positive = bigint->positive;
    new_bigint._number = (char *)malloc(bigint->lengh * sizeof(char));
    strcpy(new_bigint._number, bigint->_number);
    set_bigint_functions(&new_bigint);
    return new_bigint;
}

BigInt construct_from_string(const char *number)
{
    BigInt new_bigint;
    new_bigint.positive = true;
    int count = 0;
    if(number[0] == '-')
    {
        new_bigint.positive = false;
        count = 1;
    }
    
    new_bigint.lengh = strlen(number) - count;
    new_bigint._number = (char *)malloc(strlen(number) + 1 - count);
    strcpy(new_bigint._number, number + count);
    set_bigint_functions(&new_bigint);
    return new_bigint;

}

void clear_bigint(BigInt *bigint)
{
    if(bigint)
    {
        if(bigint->_number)
        {
            free(bigint->_number);
            bigint->lengh = 0;
            bigint->_number = NULL;
            bigint->positive = true;
        }
    }
}