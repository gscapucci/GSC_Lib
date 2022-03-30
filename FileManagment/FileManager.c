#include "FileManager.h"

//--------functions----------//
void set_file_manager_functions(FileManager *fm);

void set_file(FileManager *self, char *path);
void cat_file(FileManager *self);
void write_file(FileManager *self, void *data, size_t size_of_data);
//---------------------------//

void set_file_manager_functions(FileManager *fm)
{
    fm->Set_file = set_file;
    fm->Cat_file = cat_file;
    fm->Write_file_line = NULL;
    fm->Read_file_line = NULL;
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
        self->_file = fopen(self->_file_path, "rb");
        if(self->_file == NULL)
        {
            fprintf(stderr, "can not open file");
            exit(1);
        }
        char c;
        while((c = fgetc(self->_file)) != EOF)
        {
            printf("%c", c);
        }
        fclose(self->_file);
        return;
    }
    fprintf(stderr, "invalid input");
    exit(1);
}

void write_file(FileManager *self, void *data, size_t size_of_data)
{
    if(self && data)
    {
        self->_file = fopen(self->_file_path, "ab");
        fwrite(data, size_of_data, 1, self->_file);
        fclose(self->_file);
        return;
    }
    fprintf(stderr, "invalid input");
    exit(1);
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