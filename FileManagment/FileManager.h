#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct FileManager FileManager;

struct FileManager
{
    FILE *_file;
    char *_file_path;
    void (*Set_file)(FileManager *self, char *path);
    void (*Cat_file)(FileManager *self);
    void (*Read_file)(FileManager *self/*??, void *data, size_t size_of_data??*/); //TODO: this
    void (*Write_file)(FileManager *self /*??, void data, size_t size_of_data??*/); //TODO: this
};

FileManager createa_file_manager();
void clear_file_manager(FileManager *fm);
#endif /* FILE_MANAGER_H */