#include "list.h"
#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>

float *read_from_file(FILE *file, int num);

Status list_float_free (List *l);

int main(int argc, char *argv[])
{
  List *l1 = NULL, *l2 = NULL;
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
        list_float_free(l1);
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
        list_float_free(l1);
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
    list_float_free(l1);
    list_free(l1);
    return -1;
  }

  order = atoi(argv[2]);

  for (i = 0; i < (total / 2); i++)
  {
    e = list_popFront(l1);

    if (!e)
    {
      list_float_free(l1);
      list_free(l1);
      list_float_free(l2);
      list_free(l2);
      return -1;
    }

    float_print(stdout, e);
    fprintf(stdout, " ");

    st = list_pushInOrder(l2, e, float_cmp, order);
    if (st == ERROR)
    {
      list_float_free(l1);
      list_free(l1);
      list_float_free(l2);
      list_free(l2);
      return -1;
    }
  }
  fprintf(stdout, "\n");

  fprintf(stdout, "Now we extract from the end and insert in order:\n");
  for (i = total / 2; i < total; i++)
  {
    e = list_popBack(l1);

    if (!e)
    {
      list_float_free(l1);
      list_free(l1);
      list_float_free(l2);
      list_free(l2);
      return -1;
    }

    float_print(stdout, e);
    fprintf(stdout, " ");

    st = list_pushInOrder(l2, e, float_cmp, order);
    if (st == ERROR)
    {
      list_float_free(l1);
      list_free(l1);
      list_float_free(l2);
      list_free(l2);
      return -1;
    }
  }
  fprintf(stdout, "\n");

  list_print(stdout, l2, float_print);

  list_float_free(l1);
  list_free(l1);
  list_float_free(l2);
  list_free(l2);

  return 0;
}

Status list_float_free (List *l){
  float *aux=NULL;

  if(!l){
    return ERROR;
  }

  while(list_isEmpty(l)==FALSE){
    aux = list_popFront(l);
    if(aux!=NULL){
      free(aux);
      aux=NULL;
    }
  }

  return OK;
}