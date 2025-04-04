#include "list.c"
#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  List *l1 = NULL, *l2 = NULL;
  FILE *file = NULL;
  char *filename = NULL;
  int total = 0, i, j, order = 0;
  float number;
  void *e;

  if (argc < 3 || argc > 3)
  {
    fprintf(stderr, "Format should be: ./p3_e3 <text_file> 1 or -1\n");
    return -1;
  }

  filename = argv[1];

  file = fopen(filename, "r");

  if (!file)
  {
    return -1;
  }

  l1 = list_new();

  if (!l1)
  {
    fclose(file);
    return -1;
  }

  fscanf(file, "%d", &total);

  for (i = 0, j = 1; i < total; i++, j++)
  {
    if (!(j % 2))
    {
      fscanf(file, "%f", &number);
      list_pushFront(l1, &number);
    }
    else
    {
      fscanf(file, "%f", &number);
      list_pushBack(l1, &number);
    }
  }

  list_print(stdout, l1, float_print);

  fprintf(stdout, "Finished inserting. Now we extract from the beginning and insert in order:\n");

  l2 = list_new();
  if (!l2)
  {
    list_free(l1);
    fclose(file);
    return -1;
  }
  
  order = atoi(argv[2]);

  for (i = 0; i <= total / 2; i++)
  {
    e = list_popFront(l1);

    if (!e)
    {
      list_free(l1);
      list_free(l2);
      fclose(file);
      return -1;
    }
    
    list_pushInOrder(l2, e, float_cmp, order);
  }

  fprintf(stdout, "Now we extract from the end and insert in order:\n");

  for (i = total/2 + 1; i < total; i++)
  {
    e = list_popBack(l1);

    if (!e)
    {
      list_free(l1);
      list_free(l2);
      fclose(file);
      return -1;
    }

    list_pushInOrder(l2, e, float_cmp, order);
  }

  list_print(stdout, l2, float_print);

  list_free(l1);
  list_free(l2);
  fclose(file);
  return 0;
}