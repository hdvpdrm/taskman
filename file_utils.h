#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include<unistd.h>
#include<stdbool.h>
#include<wordexp.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<stdio.h>

bool file_exists(char *filename);
char* expand_path(const char* path);
#endif
