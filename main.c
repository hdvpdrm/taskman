#define VERSION "0.1"
#include"argparser.h"
#include"task.h"

void print_help(void);
bool prepare_taskman_file(void);
int run(int argc, char** argv);
int main(int argc, char** argv)
{
  if(!prepare_taskman_file()) return -3;

  
  return run(argc, argv);
}
void print_help(void)
{
    printf(
        "Usage: taskman [options]\n"
        "Options:\n"
        "  list [current|finished]  List tasks\n"
        "  add <title> <description> <priority>  Add a new task\n"
	"  finish <id> Set task with passed id as finished\n"
        "  --help, -h, help  Show this help message\n"
        "  --version, -v, version  Show version information\n"
        "\n"
        "Examples:\n"
        "  taskman list current  List all current tasks\n"
        "  taskman add \"Buy groceries\" \"Milk, Bread, Eggs\" 5  Add a new task with priority 5\n"
        "  taskman --version  Show the version of the program\n"
    );
}
bool prepare_taskman_file(void)
{
  char* task_file = expand_path("~/.taskman");
  if(task_file == NULL)
    {
      printf("taskman error: failed to expand path '%s'\n",task_file);
      return -2;
    }
  
  if(file_exists(task_file))return true;

  if(!create_empty_task_file(task_file))
    {
      free(task_file);
      printf("taskman errror: failed to create taskman file!\n");
      return false;
    }

  printf("created initial taskman file '%s',task_file\n");
  free(task_file);
  return true;
}
int run(int argc, char** argv)
{
  void* output = NULL;
  
  int result = parse_arguments(argc, argv,&output);
  if(result == _HELP)
    {
      print_help();
    }
  else
  if(result == _VERSION)
    {
      printf("%s\n",VERSION);
    }
  else
  if(result == _ERROR)
    {
      return -1;
    }
  else
  if(result == _ADD_TASK)
    {
      NewTask* task = (NewTask*)output;
      
      free(task->title);
      free(task->description);
      free(task);
    }
  else
  if(result == _FINISH_TASK)
    {
      int val = (int)output;
    }
  else
  if(result == _LIST_FINISHED)
    {

    }
  else
  if(result == _LIST_IN_PROGRESS)
    {
      
    }

  return 0;
}
