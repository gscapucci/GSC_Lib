#include "build.h"


#define LIB_SOURCES ARGS("global_allocator.c", "DataTypes/String.c", "DataStructures/HashMap.c", "DataStructures/Vector.c", "DataStructures/Stack.c")
#define EXE_SOURCES ARGS("main.c", LIB_SOURCES)
#define TEST_SOURCES ARGS("tests/main_test.c", LIB_SOURCES)
#define FLAGS ARGS("-Wall", "-Wextra", "-Wpedantic")

enum Options {
    NONE = (1 << 0),
    BUILD = (1 << 1),
    RUN = (1 << 2),
};

void usage() {
    printf("Usage\n");
}

int main(int argc, char **argv) {
    size_t arg_pos = 1;
    enum Options opt = BUILD;
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
                BuildSystem *build = buildsys_create("cgsc", GCC, true);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, LIB_SOURCES);
                if(opt & RUN) {
                    fprintf(stderr, "You can not run a library");
                }
                buildsys_compile(build);
                buildsys_link(build);
                buildsys_clear(build);
                break;
            }
            if(!strcmp(argv[arg_pos], "exe")) {
                BuildSystem *build = buildsys_create("main", GCC, false);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, EXE_SOURCES);
                
                buildsys_compile(build);
                buildsys_link(build);
                buildsys_clear(build);
                if(opt & RUN) {
                    char command[50] = {0};
                    sprintf(command, "./%s", "main");
                    system(command);
                }
                break;
            }
            if(!strcmp(argv[arg_pos], "test")) {
                BuildSystem *build = buildsys_create("main_test", GCC, false);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, TEST_SOURCES);

                
                buildsys_compile(build);
                buildsys_link(build);
                buildsys_clear(build);
                if(opt & RUN) {
                    char command[50] = {0};
                    sprintf(command, "./%s", "main_test");
                    system(command);
                }
                break;
            }
        default:
            usage();
            break;
    }
    return 0;
}