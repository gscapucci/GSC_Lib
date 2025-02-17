#ifndef DEFER_H
#define DEFER_H

typedef struct DeferContext{
    void (*func)(void*);
    void *arg;
}DeferContext;

void defer_cleanup(DeferContext *ctx) {
    if (ctx->func) {
        ctx->func(ctx->arg);  // Executa a função com o argumento
    }
}
#define defer(name, fun, ...) DeferContext defer_##name __attribute__((cleanup(defer_cleanup))) = {.func = (void (*)(void *))fun, .arg = (void *)__VA_ARGS__};


#endif /* DEFER_H */