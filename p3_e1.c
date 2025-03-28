#include "delivery.h"
#include "file_utils.h"
#include "vertex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Delivery *build_delivery(FILE *pf);

int main(int argc, char *argv[])
{
  FILE *file = NULL;
  char *filename;
  Delivery *d = NULL;
  Status st = OK;

  if (argc < 2)
  {
    fprintf(stderr, "Format should be: %s <File1>\n", argv[0]);
    return -1;
  }
  
  filename =argv[1];

  file = fopen(filename, "r");

  if (!file)
  {
    return -1;
  }
  
  d = build_delivery(file);

  if (!d)
  {
    return -1;
  }

  fclose(file);

  fprintf(stdout, "Running delivery plan queue: \n");
  st = delivery_run_plan(stdout, d, vertex_print, vertex_free);

  if (st == ERROR)
  {
    delivery_free(d);
    return -1;
  }

  delivery_free(d);
  return 0;
}

Delivery *build_delivery(FILE *pf)
{
  Delivery *d = NULL;
  Vertex *v = NULL;
  Status st = OK;
  char *name, *product, *aux;
  int num = 0, i;

  if (!pf)
  {
    return NULL;
  }

  fscanf(pf, "%s %s", name, product);

  d = delivery_init(name, product);

  if (!d)
  {
    return NULL;
  }
  
  fscanf(pf, "%d", &num);

  for ( i = 0; i < num; i++)
  {
    fscanf(pf, "%s", aux);
    v = vertex_initFromString(aux);

    if (!v)
    {
      return NULL;
    }
    
    st = delivery_add(stdout, d, v, vertex_print);

    if (st == ERROR)
    {
      return NULL;
    }
    
    vertex_free(v);
  }
  
  vertex_free(v);
  return d;
}