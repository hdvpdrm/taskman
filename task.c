#include"task.h"


bool create_task(char* title, char* description, short priority, int task_amount)
{
  char* path = expand_path("~/.taskman");
  if(path == NULL) return false;
  
  FILE* file = fopen(path,"r+");
  if(file == NULL)
    {
      printf("taskman error: failed to open '%s'\n",path);
      return false;
    }
  fseek(file,0,SEEK_END);
  fprintf(file,"\n\n\n[task-%d]\ntitle=%s\ndesc=%s\npriority=%d\n",task_amount+1,title,description,(int)priority);

  update_task_amount(task_amount+1,file);
  fclose(file);
  return true;
}
bool update_task_amount(int new_amount,FILE* file)
{
  const char* first_line = "records_amount = 0";
  fseek(file,strlen(first_line)-1,SEEK_SET);
  printf("%d\n",ftell(file));
  fprintf(file,"%d",new_amount);
}
bool create_empty_task_file(char* path)
{
  FILE* file = fopen(path,"w");
  if(file == NULL)
    {
      printf("taskman error: failed to open '%s'\n",path);
      return false;
    }
  fprintf(file,"records_amount = 0\n");
  fclose(file);

  return true;
}
