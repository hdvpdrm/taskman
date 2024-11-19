#ifndef TASK_H
#define TASK_H
#include<unistd.h>
#include<stdbool.h>
#include<wordexp.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include"toml.h"


bool file_exists(char *filename);
bool create_task(char* title, char* description, short priority, int task_amount);
bool create_empty_task_file(char* path);

char* expand_path(const char* path);
#endif
