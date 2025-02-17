#ifndef BUILD_H
#define BUILD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUILDSYS_ADD_SOURCES(bs, ...) \
    do { \
        const char *sources[] = {__VA_ARGS__}; \
        for (size_t i = 0; i < sizeof(sources) / sizeof(sources[0]); i++) { \
            buildsys_add_source(bs, sources[i]); \
        } \
    } while (0)

#define BUILDSYS_ADD_FLAGS(bs, ...) \
do { \
    const char *sources[] = {__VA_ARGS__}; \
    for (size_t i = 0; i < sizeof(sources) / sizeof(sources[0]); i++) { \
        buildsys_add_flag(bs, sources[i]); \
    } \
} while (0)

#define ARGS(...) __VA_ARGS__

typedef struct {
    char compiler[100];
    char **sources;
    int source_count;
    char **flags;
    int flag_count;
    char *output_name;
    bool library;
} BuildSystem;

static const char *COMPILERS[] = {
    NULL,
    "gcc",
    "clang",
    "msvc",
};

typedef enum {
    UNKNOWN = 0,
    GCC = 1,
    CLANG = 2,
    MSVC = 3,
} DefaultCompiler;

static BuildSystem *buildsys_create(const char *output_name, DefaultCompiler compiler, bool library) {
    BuildSystem *bs = (BuildSystem *)malloc(sizeof(BuildSystem));
    if(COMPILERS[(int)compiler] != NULL) {
        strcpy(bs->compiler, COMPILERS[(int)compiler]);
    }
    bs->output_name = strdup(output_name);
    bs->sources = NULL;
    bs->flags = NULL;
    bs->source_count = 0;
    bs->flag_count = 0;
    bs->library = library;
    return bs;
}


static void buildsys_destroy(BuildSystem *bs) {
    free(bs->output_name);
    for (int i = 0; i < bs->source_count; i++) {
        free(bs->sources[i]);
    }
    free(bs->sources);
    
    for (int i = 0; i < bs->flag_count; i++) {
        free(bs->flags[i]);
    }
    free(bs->flags);
    
    free(bs);
}

static void set_unknown_compiler(BuildSystem *bs, const char *compiler) {
    strcpy(bs->compiler, compiler);
}

static void buildsys_add_source(BuildSystem *bs, const char *source) {
    bs->source_count++;
    bs->sources = (char **)realloc(bs->sources, bs->source_count * sizeof(char *));
    bs->sources[bs->source_count - 1] = strdup(source);
}

static void buildsys_add_flag(BuildSystem *bs, const char *flag) {
    bs->flag_count++;
    bs->flags = (char **)realloc(bs->flags, bs->flag_count * sizeof(char *));
    bs->flags[bs->flag_count - 1] = strdup(flag);
}

static void buildsys_compile(BuildSystem *bs) {
    char flags[256] = {0};
    for(int i = 0; i < bs->flag_count; i++) {
        strcat(flags, bs->flags[i]);
        strcat(flags, " ");
    }
    for (int i = 0; i < bs->source_count; i++) {
        char command[1024];
        snprintf(command, sizeof(command), "%s %s -c %s -o %s.o", bs->compiler, flags, bs->sources[i], bs->sources[i]);
        printf("Compilando: %s\n", command);
        if(system(command) != 0) exit(1);
    }
}

static void buildsys_link_lib(BuildSystem *bs) {
    char command[512] = {0};
    snprintf(command, sizeof(command), "ld -r -o %s.o", bs->output_name);

    for (int i = 0; i < bs->source_count; i++) {
        strcat(command, " ");
        strcat(command, bs->sources[i]);
        strcat(command, ".o");
    }
    printf("Linkando: %s\n", command);
    if(system(command) != 0) exit(1);
}

static void buildsys_link(BuildSystem *bs) {
    if(bs->library) {
        buildsys_link_lib(bs);
        return;
    }
    char command[512] = {0};
    snprintf(command, sizeof(command), "%s -o %s", bs->compiler, bs->output_name);

    for (int i = 0; i < bs->source_count; i++) {
        strcat(command, " ");
        strcat(command, bs->sources[i]);
        strcat(command, ".o");
    }
    printf("Linkando: %s\n", command);
    if(system(command) != 0) exit(1);
}

static void buildsys_clear(BuildSystem *bs) {
    for(int i = 0; i < bs->source_count; i++) {
        char command[256] = {0};
        strcat(command, "rm ");
        strcat(command, bs->sources[i]);
        strcat(command, ".o");
        printf("Deletando: %s\n", command);
        if(system(command) != 0) exit(1);
    }
}
#endif /* BUILD_H */