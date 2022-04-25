#ifndef MACROS_H
#define MACROS_H

#define HERE(...) fprintf(stderr, "%s:%d: %s "__VA_ARGS__, __FILE__, __LINE__, __func__)

#define UNIMPLEMENTED\
            HERE("not implemented yet");\
            exit(1)

#define ERROR(...) \
            HERE(__VA_ARGS__); \
            exit(1)

#endif /* MACROS_H */