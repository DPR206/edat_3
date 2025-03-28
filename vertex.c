#include "vertex.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAG_LENGTH 64
struct _Vertex
{
  long id;
  char tag[TAG_LENGTH];
  Label state;
  int index;
};
/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField(Vertex *v, char *key, char *value);

Status vertex_setField(Vertex *v, char *key, char *value)
{
  if (!key || !value)
    return ERROR;

  if (strcmp(key, "id") == 0)
  {
    return vertex_setId(v, atol(value));
  }
  else if (strcmp(key, "tag") == 0)
  {
    return vertex_setTag(v, value);
  }
  else if (strcmp(key, "state") == 0)
  {
    return vertex_setState(v, (Label)atoi(value));
  } /*else if (strcmp(key, "index") == 0)
  {
    return vertex_set_index(v, atoi(value));
  }*/

  /*vertex_set_index(v, )*/
  

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr)
{
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v = NULL;

  /* Check args: */
  if (!descr)
    return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v)
    return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token)
  {
    p = strchr(token, ':');
    if (!p)
      continue;

    *p = '\0';
    key = token;
    value = p + 1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

Vertex *vertex_init()
{
  /*Initialise arguments*/
  Vertex *v = NULL;

  /*Allocate memory*/
  v = (Vertex *)calloc(1, sizeof(Vertex));

  /*Check memory*/
  if (v == NULL)
  {
    return NULL;
  }

  return v;
}

long vertex_getId(const Vertex *v)
{
  if (!v)
  {
    return -1;
  }

  return v->id;
}

const char *vertex_getTag(const Vertex *v)
{
  if (!v)
  {
    return NULL;
  }

  return v->tag;
}

Label vertex_getState(const Vertex *v)
{
  if (!v)
  {
    return ERROR_VERTEX;
  }

  return v->state;
}

Status vertex_setId(Vertex *v, const long id)
{
  if (!v || id < 0)
  {
    return ERROR;
  }

  v->id = id;

  return OK;
}

Status vertex_setTag(Vertex *v, const char *tag)
{
  if (!v || strlen(tag) > TAG_LENGTH)
  {
    return ERROR;
  }

  strcpy(v->tag, tag);
  return OK;
}

Status vertex_setState(Vertex *v, const Label state)
{
  if (!v)
  {
    return ERROR;
  }

  v->state = state;

  return OK;
}

int vertex_cmp(const void *v1, const void *v2)
{
  Vertex *w1=NULL, *w2=NULL;
  w1 = (Vertex *)v1;
  w2 = (Vertex *)v2;

  if (!w1 || !w2)
  {
    return 0;
  }

  if (vertex_getId(w1) < vertex_getId(w2))
  {
    return -1;
  }
  else if (vertex_getId(w1) > vertex_getId(w2))
  {
    return 1;
  }
  else
  {
    return strcmp(w1->tag, w2->tag);
  }
}

Status vertex_set_index(Vertex *v, int index)
{
  if (!v || index < 0)
  {
    return ERROR;
  }

  v->index = index;

  return OK;
}

int vertex_get_index(Vertex *v)
{
  if (!v)
  {
    return -1;
  }
  
  return v->index;
}

void *vertex_copy(const void *src)
{
  Vertex *cpy = NULL, *src1 = NULL;

  if (!src)
  {
    return NULL;
  }

  cpy = vertex_init();

  if (!cpy)
  {
    return NULL;
  }

  src1 = (Vertex *)src;

  if (!src1)
  {
    vertex_free(cpy);
    return NULL;
  }

  vertex_setId(cpy, vertex_getId(src1));
  vertex_setState(cpy, vertex_getState(src1));
  vertex_setTag(cpy, vertex_getTag(src1));
  vertex_set_index(cpy, vertex_get_index(src1));

  return cpy;
}

int vertex_print(FILE *pf, const void *v)
{
  Vertex *w;
  int num = 0;

  if (!pf || !v)
  {
    return -1;
  }

  w = (Vertex *)v; 

  num = fprintf(pf, "[%ld, %s, %d, %d]", vertex_getId(w), vertex_getTag(w), vertex_getState(w), (int)vertex_get_index(w));

  return num;
}

void vertex_free(void *v)
{
  free(v);
}

