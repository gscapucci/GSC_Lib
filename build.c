#include "build.h"


#define LIB_SOURCES ARGS("global_allocator.c", "DataTypes/String.c", "DataStructures/hashmap.c", "DataStructures/vector.c")
#define EXE_SOURCES ARGS("main.c", LIB_SOURCES)
#define TEST_SOURCES ARGS("tests/main_test.c", LIB_SOURCES)
#define FLAGS ARGS("-Wall", "-Wextra", "-Wpedantic")

int main(int argc, char **argv) {
    switch (argc) {
        case 2:
            if(!strcmp(argv[1], "lib")) {
                BuildSystem *build = buildsys_create("cgsc", GCC, true);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, LIB_SOURCES);

                buildsys_compile(build);
                buildsys_link(build);
                buildsys_clear(build);
                break;
            }
            if(!strcmp(argv[1], "exe")) {
                BuildSystem *build = buildsys_create("main", GCC, false);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, EXE_SOURCES);

                buildsys_compile(build);
                buildsys_link(build);
                buildsys_clear(build);
                break;
            }
            if(!strcmp(argv[1], "test")) {
                BuildSystem *build = buildsys_create("main_test", GCC, false);
                BUILDSYS_ADD_FLAGS(build, FLAGS);
                BUILDSYS_ADD_SOURCES(build, TEST_SOURCES);

                buildsys_compile(build);
                buildsys_link(build);
                buildsys_clear(build);
                break;
            }
        default:
            printf("Print Help\n");
            break;
    }
    return 0;
}