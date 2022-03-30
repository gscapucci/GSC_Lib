#include "../GSC_Lib.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "not enough files");
        exit(1);
    }
    FileManager fm = createa_file_manager();
    fm.Set_file(&fm, argv[1]);
    fm.Cat_file(&fm);
    clear_file_manager(&fm);
    return 0;
}