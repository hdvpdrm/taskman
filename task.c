#include"task.h"


bool read_taskman_file(char* path, int* tasks_len)
{
    FILE* fp;
    char errbuf[200];

    fp = fopen(path, "r");
    if (!fp)
      {
        error("cannot open sample.toml - ", strerror(errno));
	fclose(fp);
	return false;
      }

    conf = toml_parse_file(fp, errbuf, sizeof(errbuf));
    if (!conf)
      {
        error("cannot parse - ", errbuf);
	fclose(fp);
	return false;
    }

    fclose(fp);

    read_tasks_amount();
    *tasks_len = tasks_amount;
    return true;
}
void read_tasks_amount(void)
{
  toml_datum_t amount = toml_int_in(conf,"records_amount");
  if(!amount.ok)
    {
      error("failed to retrieve amount of tasks.","");
      exit(-1);
    }
  tasks_amount = (int)amount.u.i;
}
char* get_table_name(int i)
{
  int len = floor(log10(abs(i))) + 1; //old school hack.
  char* buffer = malloc(sizeof(char)*(len+5));
  if(buffer == NULL) return NULL;

  strcpy(buffer,"task-");

  char* num_buffer = malloc(sizeof(char)* len);

  if(num_buffer == NULL) return NULL;
  
  snprintf(num_buffer, len+1, "%d", i);

    for(int i = 0;i<len;++i)
   {
      buffer[i+5] = num_buffer[i];
    }
    free(num_buffer);
  
  return buffer;
}
int read_tasks(NewTask** tasks)
{
  *tasks = malloc(sizeof(NewTask)*tasks_amount);
  if(tasks == NULL) return 0;
  
  for(int i = 0;i<tasks_amount;++i)
    {
      char* table_name =  get_table_name(i+1);
      toml_table_t* task = toml_table_in(conf,table_name);
      if(!task)
	{
	  printf("taskman error: well, unable to find %s table in taskman file!",table_name);
	}
      else
	{
	  toml_datum_t title = toml_string_in(task,"title");
	  if(!title.ok)
	    {
	      printf("taskman error: failed to parse table...");
	      return -1;
	    }
	  toml_datum_t desc = toml_string_in(task,"desc");
	  if(!desc.ok)
	    {
	      printf("taskman error: failed to parse table...");
	      return -1;
	    }
	  toml_datum_t priority = toml_int_in(task,"priority");
	  if(!priority.ok)
	    {
	      printf("taskman error: failed to parse table...");
	      return -1;
	    }
	  (*tasks)[i].priority = (int)priority.u.i;
	  toml_datum_t status = toml_int_in(task,"status");
	  if(!status.ok)
	    {
	      (*tasks)[i].status = false;
	    }
	  else
	    {
	      (*tasks)[i].status = status.u.b;
	    }

	  
	  if(!set_str_values(&(*tasks)[i],title.u.s,desc.u.s))
	    {
	      printf("taskman error: failed to set string values while parsing table...");
	      return -1;
	    }
	  
	}
      free(table_name);
      
    }

  return tasks_amount;
}

bool create_task(char* title, char* description, short priority,bool status)
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

  fprintf(file,"\n\n\n[task-%d]\n"
	        "title='%s'\n"
	        "desc='%s'\n"
                "priority=%d\n"
	        "status=%d\n"
	  ,tasks_amount+1,title,description,(int)priority,(int)status);
  
  update_task_amount(tasks_amount+1,file);
  fclose(file);
  return true;
}
bool update_task_amount(int new_amount,FILE* file)
{
  const char* first_line = "records_amount = 0";
  fseek(file,strlen(first_line)-1,SEEK_SET);
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
bool mark_as_done(int task_id)
{
  char* path = expand_path("~/.taskman");
  if(path == NULL)
    {
      printf("taskman error: unable to open taskman file!\n");
      return false;
    }

  NewTask* tasks = NULL;
  if(read_tasks(&tasks) == 0)
    {
      printf("taskman error: unable to read taskman file!\n");
      return false;
    }
  
  
  if(remove(path) != 0)
    {
      printf("taskman error: unable to erase taskman file!\n");
      return false;
    }

  if(!create_empty_task_file(path))
    {
      printf("taskman error: unable to re-create taskman file!\n");
      return false;
    }

  //overal this code demonstrates why global state is not good
  int len = tasks_amount;
  tasks_amount = 0; //to reset id setting
  for(int i = 0;i<len;++i)
    {
      bool status = task_id - 1 == i?true:false;
      if(!create_task(tasks[i].title,tasks[i].description,tasks[i].priority,status))
      	{
	  printf("taskman error:failed to re-write task!\n");
	  return false;
      	}
    }
  free(tasks);
  
  return true;
}
