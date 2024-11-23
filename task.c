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
	  toml_datum_t start = toml_string_in(task,"start");
	  if(!start.ok)
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
	  if(!set_str_values(&(*tasks)[i],title.u.s,desc.u.s,start.u.s))
	    {
	      printf("taskman error: failed to set string values while parsing table...");
	      return -1;
	    }
	  
	}
      free(table_name);
      
    }

  return tasks_amount;
}

bool create_task(char* title, char* description, short priority)
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

  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char* start_time = asctime(tm);
  start_time[strlen(start_time)-1] = '\0';
  
  fprintf(file,"\n\n\n[task-%d]\n"
	        "title='%s'\n"
	        "desc='%s'\n"
                "priority=%d\n"
	        "start='%s'\n",tasks_amount+1,title,description,(int)priority,start_time);
  
  update_task_amount(tasks_amount+1,file);
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
