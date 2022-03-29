#include "FileManager.h"

//--------functions----------//
void set_file_manager_functions(FileManager *fm);

void set_file(FileManager *self, char *path);
void cat_file(FileManager *self);
//---------------------------//

void set_file_manager_functions(FileManager *fm)
{
    fm->Set_file = set_file;
    fm->Cat_file = cat_file;
    fm->Read_file = NULL;
    fm->Write_file = NULL;
}

void set_file(FileManager *self, char *path)
{
    if(self && path)
    {
        if(self->_file)
        {
            free(self->_file_path);
            self->_file_path = NULL;
        }
        self->_file_path = (char *)malloc((strlen(path) + 1) * sizeof(char));
        strcpy(self->_file_path, path);
        return;
    }
    fprintf(stderr, "invalid input");
    exit(1);
}

void cat_file(FileManager *self)
{
    if(self)
    {
        self->_file = fopen(self->_file_path, "r");
        char c;
        while((c = fgetc(self->_file)) != EOF)
        {
            printf("%c", c);
        }
        fclose(self->_file);
        return;
    }
    fprintf(stderr, "invalid input");
}

FileManager createa_file_manager()
{
    FileManager fm;
    fm._file = NULL;
    fm._file_path = NULL;
    set_file_manager_functions(&fm);
    return fm;
}

void clear_file_manager(FileManager *fm)
{
    if(fm)
    {
        if(fm->_file)
        {
            free(fm->_file);
        }
        if(fm->_file_path)
        {
            free(fm->_file_path);
        }
        fm->_file = NULL;
        fm->_file_path = NULL;
        return;
    }
    fprintf(stderr, "invalid input");
    exit(1);
}