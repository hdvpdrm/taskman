#include"task_struct.h"

bool set_str_values(NewTask* task, char* title, char* desc, char* start)
{
  if(task == NULL) return false;

  task->title = malloc(sizeof(char)*(strlen(title)+1));
  if(task->title == NULL)return false;
  strcpy(task->title, title);

  task->description = malloc(sizeof(char)*(strlen(desc)+1));
  if(task->description == NULL)return false;
  strcpy(task->description,desc);

  task->start = malloc(sizeof(char)*(strlen(start)+1));
  if(task->start == NULL) return false;
  strcpy(task->start,start);
  
  return true;
}
