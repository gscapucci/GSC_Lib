#include "build.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#define ARGS(...) __VA_ARGS__
#define LIB_SOURCES ARGS("global_allocator.c", "DataTypes/String.c", "DataStructures/HashMap.c", "DataStructures/Vector.c", "DataStructures/Stack.c")
#define EXE_SOURCES ARGS("main.c", LIB_SOURCES)
#define TEST_SOURCES ARGS("tests/main_test.c", LIB_SOURCES)
#define FLAGS ARGS("-Wall", "-Wextra", "-Wpedantic")
#define LINK ARGS("-lm", "-lquadmath")

enum Options {
    NONE = (1 << 0),
    BUILD = (1 << 1),
    RUN = (1 << 2),
};

void usage() {
    printf("Usage:\n");
    printf("./build%s lib\n", get_executable_extension());
    printf("./build%s test\n", get_executable_extension());
    printf("./build%s [file.c]\n", get_executable_extension());
}


int main(int argc, char **argv) {
    size_t arg_pos = 1;
    enum Options opt = BUILD;
    CompilerType compiler = detect_compiler();
    setbuf(stdout, NULL);
    switch (compiler) {
        case COMPILER_GCC:
            printf("Using GCC compiler for %s\n", get_os());
            break;
        case COMPILER_CLANG:
            printf("Using CLANG compiler for %s\n", get_os());
            break;
        case COMPILER_MSVC:
            printf("Using MSVC compiler for %s\n", get_os());
            break;
        case COMPILER_UNKNOWN:
            printf("Unknown compiler, aborting...");
            exit(1);
            break;
    }
    if (!is_libquadmath_installed()) {
        fprintf(stderr, "Error: libquadmath is not installed on the system.\n");
        fprintf(stderr, "Please install the library before proceeding.\n");
    #if defined(__linux__)
        fprintf(stderr, "On Linux, use: sudo apt-get install libquadmath0\n");
    #elif defined(_WIN32)
        fprintf(stderr, "On Windows, install MinGW or MSYS2 with libquadmath support.\n");
    #elif defined(__APPLE__)
        fprintf(stderr, "On macOS, install GCC via Homebrew: brew install gcc\n");
    #endif
        exit(1);
    }
    fflush(stdout);
    // printf("Test\n");
    switch (argc) {
        case 3:
            if(!strcmp(argv[arg_pos], "-r") || !strcmp(argv[arg_pos], "-run")) {
                arg_pos++;
                opt |= RUN;
            } else {
                usage();
                break;
            }
        case 2:
            if(!strcmp(argv[arg_pos], "lib")) {
                BuildSystem *build = buildsys_create("cgsc", compiler, true);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, LIB_SOURCES);
                BUILDSYS_ADD_LINKS(build, LINK);
                if(opt & RUN) {
                    fprintf(stderr, "You can not run a library");
                }
                buildsys_compile(build, compiler);
                buildsys_link(build, compiler);
                buildsys_clear(build);
                fflush(stdout);
                break;
            }
            if(!strcmp(argv[arg_pos], "test")) {
                BuildSystem *build = buildsys_create("main_test", compiler, false);
                BUILDSYS_ADD_FLAGS(build, "-g", FLAGS);
                BUILDSYS_ADD_SOURCES(build, TEST_SOURCES);

                
                buildsys_compile(build, compiler);
                buildsys_link(build, compiler);
                buildsys_clear(build);
                if(opt & RUN) {
                    char command[200] = {0};
                    sprintf(command, "valgrind --track-origins=yes --leak-check=full ./%s", "main_test");
                    system(command);
                }
                break;
            }
            if(!strcmp(argv[arg_pos] + strlen(argv[arg_pos]) - strlen(".c"), ".c")) {
                BuildSystem *build = buildsys_create("main", compiler, false);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, argv[arg_pos], LIB_SOURCES);
                
                buildsys_compile(build, compiler);
                buildsys_link(build, compiler);
                buildsys_clear(build);
                if(opt & RUN) {
                    if (opt & RUN) {
                        char command[50] = {0};
                        #ifdef OS_WINDOWS
                            snprintf(command, sizeof(command), "%s%s", build->output_name, get_executable_extension());
                        #else
                            snprintf(command, sizeof(command), "./%s", build->output_name);
                        #endif
                        system(command);
                    }
                }
                break;
            }
        default:
            usage();
            break;
    }
    return 0;
}