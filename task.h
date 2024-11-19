#ifndef TASK_H
#define TASK_H
#include<string.h>
#include<stdlib.h>
#include"file_utils.h"
#include"toml.h"

bool create_task(char* title, char* description, short priority, int task_amount);
bool update_task_amount(int new_amount,FILE* file);

bool create_empty_task_file(char* path);


#endif
