# GSC_Lib
## Everything is in test
Create a main.c file to start:<br/>
```c
#include "GSC_Lib.h"

int main() {
    Stack stack = create_stack(10, sizeof(size_t), STACK_COPY);
    for (size_t i = 0; i < 10; i++) {
        stack_push(&stack, &i);
    }

    for (size_t i = 0; i < 10; i++) {
        size_t num;
        stack_pop(&stack, &num);
        printf("%zu\n", num);
    }
    delete_stack(&stack);
    return 0;
}
```
Getting started - Build Library:<br/>
I am using gcc but you can use any C compiler.
```bash
gcc build.c -o build
./build lib
```
Linking:
```bash
gcc -o main main.c cgsc.o
```
Or you can build directly:
```bash
./build main.c
```
You can add '-r' or '-run' to build and run:
```bash
./build -r main.c
```