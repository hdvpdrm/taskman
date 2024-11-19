#include"file_utils.h"


bool file_exists(char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
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

