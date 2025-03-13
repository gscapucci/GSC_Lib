#ifndef BUILD_H
#define BUILD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
    #define OS_WINDOWS
#elif defined(__APPLE__)
    #define OS_MACOS
#elif defined(__linux__)
    #define OS_LINUX
#else
    #define OS_UNKNOWN
#endif

const char *get_os() {
    #ifdef _WIN64
        return "Windows (64-bit)";
    #elif _WIN32
        return "Windows (32-bit)";
    #elif __APPLE__ || __MACH__
        return "macOS";
    #elif __linux__
        return "Linux";
    #elif __FreeBSD__
        return "FreeBSD";
    #elif __unix || __unix__
        return "Unix";
    #else
        return "Sistema Operacional Desconhecido";
    #endif
}

#define BUILDSYS_ADD_LINKS(bs, ...) \
    do { \
        const char *sources[] = {__VA_ARGS__}; \
        for (size_t i = 0; i < sizeof(sources) / sizeof(sources[0]); i++) { \
            buildsys_add_link(bs, sources[i]); \
        } \
    } while (0)

#define BUILDSYS_ADD_SOURCES(bs, ...) \
    do { \
        const char *sources[] = {__VA_ARGS__}; \
        for (size_t i = 0; i < sizeof(sources) / sizeof(sources[0]); i++) { \
            buildsys_add_source(bs, sources[i]); \
        } \
    } while (0)

#define BUILDSYS_ADD_FLAGS(bs, ...) \
    do { \
        const char *flags[] = {__VA_ARGS__}; \
        for (size_t i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) { \
            buildsys_add_flag(bs, flags[i]); \
        } \
    } while (0)

typedef struct {
    char compiler[100];
    char **sources;
    int source_count;
    char **flags;
    int flag_count;
    char **links;
    int link_count;
    char *output_name;
    bool library;
} BuildSystem;

static const char *COMPILERS[] = {
    NULL,
    "gcc",
    "clang",
    "cl",
};

typedef enum {
    COMPILER_UNKNOWN = 0,
    COMPILER_GCC,
    COMPILER_CLANG,
    COMPILER_MSVC,
} CompilerType;

static CompilerType detect_compiler() {
    const char *cc = getenv("CC"); // Verifica se o usuário definiu um compilador

    if (cc != NULL) {
        if (strstr(cc, "gcc") != NULL) {
            return COMPILER_GCC;
        } else if (strstr(cc, "clang") != NULL) {
            return COMPILER_CLANG;
        } else if (strstr(cc, "cl") != NULL) { // MSVC usa "cl.exe"
            return COMPILER_MSVC;
        }
    }

    // Se a variável CC não estiver definida, tente detectar o compilador manualmente
    #if defined(__GNUC__) && !defined(__clang__)
        return COMPILER_GCC;
    #elif defined(__clang__)
        return COMPILER_CLANG;
    #elif defined(_MSC_VER)
        return COMPILER_MSVC;
    #else
        return COMPILER_UNKNOWN;
    #endif
}

static BuildSystem *buildsys_create(const char *output_name, CompilerType compiler, bool library) {
    BuildSystem *bs = (BuildSystem *)malloc(sizeof(BuildSystem));
    if (!bs) {
        perror("Erro ao alocar memória para BuildSystem");
        exit(EXIT_FAILURE);
    }

    if (COMPILERS[(int)compiler] != NULL) {
        strcpy(bs->compiler, COMPILERS[(int)compiler]);
    } else {
        strcpy(bs->compiler, "gcc"); // Fallback para GCC
    }

    bs->output_name = strdup(output_name);
    bs->sources = NULL;
    bs->flags = NULL;
    bs->links = NULL;
    bs->link_count = 0;
    bs->source_count = 0;
    bs->flag_count = 0;
    bs->library = library;
    return bs;
}



static void buildsys_destroy(BuildSystem *bs) {
    if (!bs) return;

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

static const char *get_compiler_name(CompilerType compiler) {
    switch (compiler) {
        case COMPILER_GCC: return "gcc";
        case COMPILER_CLANG: return "clang";
        case COMPILER_MSVC: return "cl";
        default: return "gcc"; // Fallback para GCC
    }
}

static const char *get_object_extension() {
    #ifdef OS_WINDOWS
        return ".obj";
    #else
        return ".o";
    #endif
}

static const char *get_executable_extension() {
    #ifdef OS_WINDOWS
        return ".exe";
    #else
        return "";
    #endif
}

static const char *get_clean_command() {
    #ifdef OS_WINDOWS
        return "del";
    #else
        return "rm";
    #endif
}

static void buildsys_add_source(BuildSystem *bs, const char *source) {
    bs->source_count++;
    bs->sources = (char **)realloc(bs->sources, bs->source_count * sizeof(char *));
    if (!bs->sources) {
        perror("Erro ao realocar memória para sources");
        exit(EXIT_FAILURE);
    }
    bs->sources[bs->source_count - 1] = strdup(source);
}

static void buildsys_add_flag(BuildSystem *bs, const char *flag) {
    bs->flag_count++;
    bs->flags = (char **)realloc(bs->flags, bs->flag_count * sizeof(char *));
    if (!bs->flags) {
        perror("Erro ao realocar memória para flags");
        exit(EXIT_FAILURE);
    }
    bs->flags[bs->flag_count - 1] = strdup(flag);
}

static void buildsys_add_link(BuildSystem *bs, const char *flag) {
    bs->link_count++;
    bs->links = (char **)realloc(bs->links, bs->link_count * sizeof(char *));
    if (!bs->links) {
        perror("Erro ao realocar memória para flags");
        exit(EXIT_FAILURE);
    }
    bs->links[bs->link_count - 1] = strdup(flag);
}


static void buildsys_compile(BuildSystem *bs, CompilerType compiler) {
    char flags[1024] = {0};
    for (int i = 0; i < bs->flag_count; i++) {
        strcat(flags, bs->flags[i]);
        strcat(flags, " ");
    }

    const char *object_ext = get_object_extension();

    for (int i = 0; i < bs->source_count; i++) {
        char command[2048];
        char source_path[256];
        strcpy(source_path, bs->sources[i]);

        // Substitui barras por barras invertidas no Windows
        #ifdef OS_WINDOWS
            for (char *p = source_path; *p; p++) {
                if (*p == '/') *p = '\\';
            }
        #endif

        snprintf(command, sizeof(command), "%s %s -c %s -o %s%s", 
                  get_compiler_name(compiler), flags, source_path, source_path, object_ext);
        printf("Compilando: %s\n", command);
        if (system(command) != 0) {
            fprintf(stderr, "Erro ao compilar %s\n", source_path);
            exit(EXIT_FAILURE);
        }
    }
}


static void buildsys_link(BuildSystem *bs, CompilerType compiler) {
    char command[2048] = {0};
    const char *object_ext = get_object_extension();
    const char *executable_ext = get_executable_extension();

    if (compiler == COMPILER_MSVC) {
        // Comando do MSVC
        if (bs->library) {
            snprintf(command, sizeof(command), "link /OUT:%s.lib", bs->output_name);
        } else {
            snprintf(command, sizeof(command), "link /OUT:%s%s", bs->output_name, executable_ext);
        }

        for (int i = 0; i < bs->source_count; i++) {
            strcat(command, " ");
            strcat(command, bs->sources[i]);
            strcat(command, object_ext);
        }
    } else {
        // Comando do GCC/Clang
        if (bs->library) {
            snprintf(command, sizeof(command), "ar rcs lib%s.a", bs->output_name);
            for (int i = 0; i < bs->source_count; i++) {
                strcat(command, " ");
                strcat(command, bs->sources[i]);
                strcat(command, get_object_extension());
            }
        } else {
            snprintf(command, sizeof(command), "%s -o %s%s", get_compiler_name(compiler), bs->output_name, executable_ext);
            for (int i = 0; i < bs->source_count; i++) {
                strcat(command, " ");
                strcat(command, bs->sources[i]);
                strcat(command, get_object_extension());
            }
            for (int i = 0; i < bs->link_count; i++) {
                strcat(command, " ");
                strcat(command, bs->links[i]);  // Aqui os links só são adicionados se for um executável
            }
        }
    }


    printf("Linkando: %s\n", command);
    if (system(command) != 0) {
        fprintf(stderr, "Erro ao linkar\n");
        exit(EXIT_FAILURE);
    }
}
static void buildsys_clear(BuildSystem *bs) {
    const char *clean_command = get_clean_command();
    const char *object_ext = get_object_extension();

    for (int i = 0; i < bs->source_count; i++) {
        char command[500];
        char source_path[256];
        strcpy(source_path, bs->sources[i]);

        // Substitui barras por barras invertidas no Windows
        #ifdef OS_WINDOWS
            for (char *p = source_path; *p; p++) {
                if (*p == '/') *p = '\\';
            }
        #endif

        snprintf(command, sizeof(command), "%s %s%s", clean_command, source_path, object_ext);
        printf("Deletando: %s\n", command);
        if (system(command) != 0) {
            fprintf(stderr, "Erro ao deletar %s%s\n", source_path, object_ext);
        }
    }
}

bool is_libquadmath_installed() {
    int result;
#if defined(__linux__) || defined(__APPLE__)
    // Verifica no Linux ou macOS usando ldconfig ou find
    result = system("ldconfig -p | grep libquadmath > /dev/null 2>&1");
    if (result != 0) {
        result = system("find /usr/lib /usr/local/lib -name 'libquadmath*' > /dev/null 2>&1");
    }
#elif defined(_WIN32)
    // Verifica no Windows usando where (ou dir)
    result = system("where libquadmath.dll > nul 2>&1");
    if (result != 0) {
        result = system("dir C:\\MinGW\\lib\\libquadmath.* > nul 2>&1");
    }
#endif
    return (result == 0); // Retorna true se a biblioteca estiver instalada
}


#endif /* BUILD_H */