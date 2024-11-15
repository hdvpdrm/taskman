#define VERSION "0.1"
#include"argparser.h"


int main(int argc, char** argv)
{
  void* output = NULL;
  
  int result = parse_arguments(argc, argv,&output);
  if(result == _HELP)
    {

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
    }

  return 0;
}
