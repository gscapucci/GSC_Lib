#include "FileManager.h"

//--------functions----------//
void set_file_manager_functions(FileManager *fm);

void set_file(FileManager *self, char *path);
void cat_file(FileManager *self);
void write_file_line(FileManager *self, void *data, size_t size_of_data);
void read_file_line(FileManager *self, void *data, size_t size_of_data);
size_t get_file_size(FileManager *self);
size_t get_line_size(FileManager *self);
void set_pos(FileManager *self, size_t pos);
void set_pos_beg(FileManager *self);
void set_pos_end(FileManager *self);
void truncate(FileManager *self);
void write_file(FileManager *self, void *data, size_t size_of_data);
//---------------------------//

void set_file_manager_functions(FileManager *fm)
{
    fm->Set_file = set_file;
    fm->Cat_file = cat_file;
    fm->Write_file_line = write_file_line;
    fm->Read_file_line = read_file_line;
    fm->Get_file_size = get_file_size;
    fm->Set_pos = set_pos;
    fm->Set_pos_beg = set_pos_beg;
    fm->Set_pos_end = set_pos_end;
    fm->Truncate = truncate;
    fm->Write_file = write_file;
    fm->Get_line_size = get_line_size;
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
        self->_file = fopen(path, "ab");
        fclose(self->_file);
        return;
    }
    fprintf(stderr, "invalid input in function set_file");
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
    fprintf(stderr, "invalid input in function cat_file");
    exit(1);
}

void write_file_line(FileManager *self, void *data, size_t size_of_data)
{
    if(self && data)
    {
        self->Write_file(self, data, size_of_data);
        self->_file = fopen(self->_file_path, "r+b");
        fseek(self->_file, self->_file_pos, SEEK_SET);
        fwrite(&(char){'\n'}, sizeof(char), 1, self->_file);
        fclose(self->_file);
        self->_file_pos += sizeof(char);
        return;
    }
    fprintf(stderr, "invalid input in function write_file_line");
    exit(1);
}

void read_file_line(FileManager *self, void *data, size_t size_of_data)
{
    if(self && data)
    {
        self->_file = fopen(self->_file_path, "rb");
        char c;
        size_t line_len = 0;
        fseek(self->_file, self->_file_pos, SEEK_SET);
        while ((c = fgetc(self->_file)) != '\n')
        {
            line_len++;
        }
        fseek(self->_file, self->_file_pos, SEEK_SET);
        self->_file_pos += line_len + 1;
        if(size_of_data < line_len)
        {
            fprintf(stderr, "alloc memory to read this line POS: %zu", ftell(self->_file) - line_len);
            exit(1);
        }
        if(size_of_data > line_len)
        {
            fprintf(stderr, "WARNNING: you allocate to much memory to read this line POS: %zu\nYou need %zu, you allocate %zu\n", ftell(self->_file) - line_len, line_len, size_of_data);
        }
        fread(data, line_len, 1, self->_file);
        fseek(self->_file, self->_file_pos, SEEK_SET);
        fclose(self->_file);
        return;
    }
    fprintf(stderr, "invalid input in function read_file_line");
    exit(1);
}

size_t get_file_size(FileManager *self)
{
    if(self)
    {
        self->_file = fopen(self->_file_path, "rb");
        fseek(self->_file, 0, SEEK_END);
        size_t size = ftell(self->_file);
        fclose(self->_file);
        return size;
    }
    fprintf(stderr, "invalid input in function get_file_size");
    exit(1);
}

size_t get_line_size(FileManager *self)
{
    if(self)
    {
        self->_file = fopen(self->_file_path, "r+b");
        fseek(self->_file, self->_file_pos, SEEK_SET);
        char c;
        size_t line_size = 0;
        while((c = fgetc(self->_file)) != '\n')
        {
            line_size++;
        }
        return line_size;
    }
    fprintf(stderr, "invalid input in function get_line_size");
    exit(1);
}

void set_pos(FileManager *self, size_t pos)
{
    if(self)
    {
        size_t file_size = self->Get_file_size(self);
        if(pos > file_size)
        {
            fprintf(stderr, "max pos for tis file is %zu", file_size);
            exit(1);
        }
        self->_file_pos = pos;
        return;
    }
    fprintf(stderr, "invalid input in function set_pos");
    exit(1);
}

void set_pos_beg(FileManager *self)
{
    if(self)
    {
        self->_file_pos = 0;
        return;
    }
    fprintf(stderr, "invalid input in function set_pos_beg");
    exit(1);
}

void set_pos_end(FileManager *self)
{
    if(self)
    {
        self->_file_pos = self->Get_file_size(self);
        return;
    }
    fprintf(stderr, "invalid input in function set_pos_end");
    exit(1);
}

void truncate(FileManager *self)
{
    if(self)
    {
        self->_file = fopen(self->_file_path, "w");
        fclose(self->_file);
        return;
    }
    fprintf(stderr, "invalid input in function truncate");
    exit(1);
}

void write_file(FileManager *self, void *data, size_t size_of_data)
{
    if(self)
    {
        self->_file = fopen(self->_file_path, "r+b");
        fseek(self->_file, self->_file_pos, SEEK_SET);
        fwrite(data, size_of_data, 1, self->_file);
        fclose(self->_file);
        self->_file_pos += size_of_data;
        return;
    }
    fprintf(stderr, "invalid input in function write_file");
    exit(1);
}

FileManager createa_file_manager()
{
    FileManager fm;
    fm._file_pos = 0;
    fm._file = NULL;
    fm._file_path = NULL;
    set_file_manager_functions(&fm);
    return fm;
}

void clear_file_manager(FileManager *fm)
{
    if(fm)
    {
        if(ftell(fm->_file) >= 0)
        {
            fclose(fm->_file);
        }
        if(fm->_file_path)
        {
            free(fm->_file_path);
        }
        fm->_file = NULL;
        fm->_file_path = NULL;
        return;
    }
    fprintf(stderr, "invalid input in function clear_file_manager");
    exit(1);
}