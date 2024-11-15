#define VERSION "0.1"
#include"argparser.h"


void print_help(void);
int main(int argc, char** argv)
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
