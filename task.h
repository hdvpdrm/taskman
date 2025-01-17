#ifndef TASK_H
#define TASK_H
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include"task_struct.h"
#include"file_utils.h"
#include"toml.h"

static toml_table_t* conf;
static int tasks_amount = 0;

static void error(const char* msg, const char* msg1)
{
    fprintf(stderr, "taskman error: %s%s\n", msg, msg1?msg1:"");
    exit(1);
}
bool read_taskman_file(char* path,int* tasks_len);
void read_tasks_amount(void);

char* get_table_name(int i);
int read_tasks(NewTask** tasks);

bool create_task(char* title, char* description, short priority,bool status);
bool update_task_amount(int new_amount,FILE* file);

bool create_empty_task_file(char* path);

bool mark_as_done(int task_id);

#endif
