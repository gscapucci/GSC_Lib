// #include "GSC_Lib.h"
#include "numdef.h"
#include <stdio.h>

int main() {
    f128 num = __FLT128_MAX__;
    char buf[10] = {0};
    f128_to_str(buf, 10, 10, num);
    printf("%s", buf);
    return 0;
}