#include"task.h"


bool file_exists(char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}
bool create_task(char* title, char* description, short priority)
{
  
}
bool create_empty_task_file(char* path)
{
  FILE* file = fopen(path,"w");
  if(file == NULL)
    {
      printf("taskman error: failed to open '%s'\n",path);
      return false;
    }
  fprintf(file,"records_amount = 0");
  fclose(file);

  return true;
}

char* expand_path(const char* path)
{
    wordexp_t p;
    char** w;
    int i;

    // Initialize the wordexp_t structure
    if (wordexp(path, &p, 0) != 0)
        return NULL;

    // Allocate memory for the expanded path
    w = p.we_wordv;
    if (w == NULL || w[0] == NULL)
      {
        wordfree(&p);
        return NULL;
    }

    // Copy the expanded path to a new string
    char* expanded_path = strdup(w[0]);
    if (expanded_path == NULL)
      {
        wordfree(&p);
        return NULL;
    }

    // Free the memory allocated by wordexp
    wordfree(&p);

    return expanded_path;

}
