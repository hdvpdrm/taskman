#ifndef TASK_STRUCT_H
#define TASK_STRUCT_H
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct
{
  short priority;
  char* title;
  char* description;
  char* start;
} NewTask;

bool set_str_values(NewTask* task, char* title, char* desc, char* start);


#endif
