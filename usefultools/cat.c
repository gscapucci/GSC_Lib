#include "../GSC_Lib.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "not enough files");
        exit(1);
    }
    FileManager fm = createa_file_manager();
    for (size_t i = 1; i < argc; i++)
    {
        fm.Set_file(&fm, argv[i]);
        printf("\n\nFILE: %s:\n\n", argv[i]);
        fm.Cat_file(&fm);
    }
    clear_file_manager(&fm);
    return 0;
}