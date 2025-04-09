#include "list.h"
#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>

float *read_from_file(FILE *file, int num);

int main(int argc, char *argv[])
{
  List *l1 = NULL, *l2 = NULL, *l3 = NULL, *l4=NULL;
  FILE *file = NULL;
  Status st = OK;
  char *filename = NULL;
  int total = 0, i, order = 0;
  void *e;
  float *number=NULL, n;

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

  for (i = 0; i < total; i++)
  {
    fscanf(file, "%f", &n);
    number = float_init(n);

    if (i % 2)
    {
      st = list_pushFront(l1, number);
      if (st == ERROR)
      {
        list_free(l1);
        fclose(file);
        return -1;
      }
  
    }
    else
    {
      st = list_pushBack(l1, number);
      if (st == ERROR)
      {
        list_free(l1);
        fclose(file);
        return -1;
      }
    }
  }
  list_print(stdout, l1, float_print);
  fclose(file);

  fprintf(stdout, "Finished inserting. Now we extract from the beginning and insert in order:\n");

  l2 = list_new();
  if (!l2)
  {
    list_free(l1);
    return -1;
  }
  l3 = list_new();
  if (!l3)
  {
    list_free(l1);
    list_free(l2);
    return -1;
  }
  l4 = list_new();
  if (!l4)
  {
    list_free(l1);
    list_free(l2);
    list_free(l3);
    return -1;
  }

  order = atoi(argv[2]);

  for (i = 0; i < (total / 2); i++)
  {
    e = list_popFront(l1);

    if (!e)
    {
      list_free(l1);
      list_free(l2);
      list_free(l3);
      return -1;
    }

    st = list_pushBack(l2, e);
    if (st == ERROR)
    {
      list_free(l1);
      list_free(l2);
      list_free(l3);
      return -1;
    }

    st = list_pushInOrder(l4, e, float_cmp, order);
    if (st == ERROR)
    {
      list_free(l1);
      list_free(l2);
      list_free(l3);
      return -1;
    }
  }
  list_print(stdout, l2, float_print);

  fprintf(stdout, "Now we extract from the end and insert in order:\n");
  for (i = total / 2; i < total; i++)
  {
    e = list_popBack(l1);

    if (!e)
    {
      list_free(l1);
      list_free(l2);
      list_free(l3);
      return -1;
    }

    st = list_pushBack(l3, e);
    if (st == ERROR)
    {
      list_free(l1);
      list_free(l2);
      list_free(l3);
      return -1;
    }

    st = list_pushInOrder(l4, e, float_cmp, order);
    if (st == ERROR)
    {
      list_free(l1);
      list_free(l2);
      list_free(l3);
      return -1;
    }
  }
  list_print(stdout, l3, float_print);

  list_print(stdout, l4, float_print);

  list_free(l1);
  list_free(l2);
  list_free(l3);
  list_free(l4);

  return 0;
}