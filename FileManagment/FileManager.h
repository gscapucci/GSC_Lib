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
    size_t _file_pos;

    void (*Set_file)(FileManager *self, char *path);
    void (*Cat_file)(FileManager *self);
    void (*Set_pos)(FileManager *self, size_t pos);
    void (*Set_pos_beg)(FileManager *self);
    void (*Set_pos_end)(FileManager *self);
    size_t (*Get_file_size)(FileManager *self);
    size_t (*Get_line_size)(FileManager *self);
    void (*Read_file_line)(FileManager *self, void *data, size_t size_of_data);
    void (*Write_file_line)(FileManager *self, void *data, size_t size_of_data);
    void (*Read_file)(FileManager *self, void *data, size_t size_of_data); //TODO
    void (*Write_file)(FileManager *self, void *data, size_t size_of_data);
    void (*Truncate)(FileManager *self);
};

FileManager createa_file_manager();
void clear_file_manager(FileManager *fm);
#endif /* FILE_MANAGER_H */