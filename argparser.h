#ifndef ARGPARSER_H
#define ARGPARSER_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"util_functions.h"

#define _ERROR -1
#define _HELP 1
#define _VERSION 2

#define _LIST_IN_PROGRESS 3
#define _LIST_FINISHED 4

#define _ADD_TASK 5

#define _FINISH_TASK 6

typedef struct
{
  short priority;
  char* title;
  char* description;
} NewTask;

short parse_list(char* list_option);
short parse_add(int argc, char** argv, NewTask* task);
short parse_arguments(int argc, char** argv, void** output);



#endif
