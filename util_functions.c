#include"util_functions.h"


bool is_str_digit(char* str)
{
  for(int i = 0;i<strlen(str);++i)
    {
      if(!isdigit(str[i])) return false;
    }

  return true;
}
