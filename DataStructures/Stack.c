#include "Stack.h"

Stack create_stack(size_t init_size, size_t data_size, StackMode mode) {
    Stack stack;
    stack.capacity = init_size;
    stack.data_size = data_size;
    stack.mode = mode;
    stack.items = allocate(init_size * data_size);
    stack.size = 0;
    return stack;
}
void delete_stack(Stack *stack) {
    if(!stack) return;
    if(!stack->items) return;
    deallocate(stack->items);
    stack->capacity = 0;
    stack->data_size = 0;
    stack->items = NULL;
    stack->size = 0;
}

void stack_push(Stack *stack, void *data) {
    if(stack->size >= stack->capacity) {
        stack_reserve(stack, stack->capacity ? stack->capacity * 2 : 1);
    }
    void *dest = (char *)stack->items + (stack->data_size * stack->size);
    if(stack->mode == STACK_COPY) {
        memcpy(dest, data, stack->data_size);
    } else {
        *(void **)dest = data;
    }
    stack->size++;
}

void stack_pop(Stack *stack, void *out) {
    if (stack->size == 0) {
        return; // Stack vazia
    }

    stack->size--;
    void *src = (char *)stack->items + (stack->data_size * stack->size);

    if (stack->mode == STACK_COPY) {
        if (out) {
            memcpy(out, src, stack->data_size); // Copia os dados para o buffer do usuário
        }
    } else { // STACK_MOVE
        if (out) {
            *(void **)out = *(void **)src; // Retorna o ponteiro armazenado
        }
        *(void **)src = NULL; // Evita acesso acidental ao ponteiro movido
    }
}

void stack_peek(Stack *stack, void *out) {
    if (stack->size == 0) {
        return; // Pilha vazia, não há nada para acessar
    }

    void *src = (char *)stack->items + (stack->data_size * (stack->size - 1));

    if (stack->mode == STACK_COPY) {
        if (out) {
            memcpy(out, src, stack->data_size); // Copia os dados para o buffer do usuário
        }
    } else { // STACK_MOVE
        if (out) {
            *(void **)out = *(void **)src; // Retorna o ponteiro armazenado sem removê-lo
        }
    }
}

bool stack_is_empty(const Stack *stack) {
    return stack->size == 0;
}

bool stack_reserve(Stack *stack, size_t new_capacity) {
    if (new_capacity <= stack->capacity) {
        return true; // Nada a fazer
    }

    void *new_items = realloc(stack->items, new_capacity * stack->data_size);
    if (!new_items) {
        return false; // Falha na alocação
    }

    stack->items = new_items;
    stack->capacity = new_capacity;
    return true;
}

void stack_clear(Stack *stack) {
    stack->size = 0;
}

void stack_shrink_to_fit(Stack *stack) {
    if (stack->size == stack->capacity) {
        return; // Já está no tamanho ideal
    }

    void *new_items = realloc(stack->items, stack->size * stack->data_size);
    if (!new_items && stack->size > 0) {
        return; // Falha na realocação, mantém o estado atual
    }

    stack->items = new_items;
    stack->capacity = stack->size;
}