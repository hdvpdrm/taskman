#include"argparser.h"

short parse_list(char* list_option)
{
  if(strcmp(list_option,"current") == 0)
    return _LIST_IN_PROGRESS;
  else
  if(strcmp(list_option,"finished") == 0)
    return _LIST_FINISHED;
  else
    {
      printf("taskman error: 'list' does not have '%s' option!\n",list_option);
      return _ERROR;
    }
}
short parse_add(int argc, char** argv, NewTask* task)
{
  task->title = (char*)malloc(sizeof(char)*strlen(argv[2]) + 1);
  if(task->title == NULL)
    {
      printf("taskman error: shit happened while trying to allocate new memory!\n");
      return _ERROR;
    }
  
  strcpy(task->title,argv[2]);

  
  task->description = (char*)malloc(sizeof(char)*strlen(argv[3]) + 1);
  if(task->description == NULL)
    {
      printf("taskman error: shit happened while trying to allocate new memory!\n");
      return _ERROR;
    }
  strcpy(task->description,argv[3]);
  if(!is_str_digit(argv[4]))
    {
      printf("taskman error: third argument of 'add' should be integer!\n");
      return _ERROR;
    }
  int priority = atoi(argv[4]);
  if(priority > 10 ||
     priority < 0)
    {
      printf("taskman error: priority should be in [0,10]!\n");
      return _ERROR;
    }
  task->priority = (short)priority;

  return 0;
}
short parse_arguments(int argc, char** argv, void** output)
{
  if(argc <= 1) return _ERROR;
  if(argc == 1) return _HELP;
  

  if(strcmp(argv[1],"list") == 0)
    {
      if(argc != 3)
	{
	  printf("taskman error: 'list' option supposes to have only 2 arguments!\n");
	  return _ERROR;
	}

      return parse_list(argv[2]);
    }
  else
  if(strcmp(argv[1],"add") == 0)
    {
      if(argc != 5)
	{
	  printf("taskman error: 'add' option supposes to have only 3 arguments!\n");
	  return _ERROR;
	}
      
      *output = (void*)malloc(sizeof(NewTask));
      if(*output == NULL)
	{
	  printf("taskman error: shit happened while trying to allocate new memory!\n");
	  return _ERROR;
	}

      if(parse_add(argc,argv,(NewTask*) *output) == 0)
	return _ADD_TASK;
      else
	{
	  free(*output);
	  return _ERROR;
	}
    }
  else
  if(strcmp(argv[1],"finish") == 0)
    {
      if(argc != 3)
	{
	  printf("taskman error: 'finish' option supposes to have only 1 argument!\n");
	  return _ERROR;
	}
      *output = malloc(sizeof(int));
      if(*output == NULL)
	{
	  printf("taskman error: shit happened while trying to allocate new memory!\n");
	  return _ERROR;
	}

      if(!is_str_digit(argv[2]))
	{
	  printf("taskman error:value you provided to 'finish' command should be integer!\n");
	  free(*output);
	  return _ERROR;
	}
	*output = (void*)atoi(argv[2]);
	return _FINISH_TASK;
    }
  else
  if(strcmp(argv[1],"--help") == 0 ||
     strcmp(argv[1],"-h")     == 0 ||
     strcmp(argv[1],"help")   == 0
     )
    {
      if(argc != 2)
	{
	  printf("taskman error: 'help' option supposes to have no other options!\n");
	  return _ERROR;
	}
      return _HELP;
    }
  else
  if(strcmp(argv[1],"--version") == 0 ||
     strcmp(argv[1],"-v")        == 0 ||
     strcmp(argv[1],"version")   == 0
     )
    {
      if(argc != 2)
	{
	  printf("taskman error: 'version' optino supposes to have no other options\n");
	  return _ERROR;	      
	}
      return _VERSION;
    }
  else
    {
      printf("taskman error: '%s' doesn't seem like existing argument!\n",argv[1]);
      return _ERROR;
    }
}
