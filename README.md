# GSC_Lib
## Everything is in test
Create a main.c file to start:<br/>
```c
#include "GSC_Lib.h"

int main(int argc, char **argv)
{
    Stack stack = create_stack(0);
    for (size_t i = 0; i < 10; i++)
    {
        stack.push(&stack, &i, sizeof(size_t));
    }

    for (size_t i = 0; i < 10; i++)
    {
        size_t num = *(size_t *)stack.pop(&stack);
        printf("%lld\n", num);
    }
    clear_stack(&stack);
    return 0;
}
```
Type this command to run:
```bash
make run
```
