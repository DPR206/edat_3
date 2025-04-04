#include "list.h"
#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NodeList
{
  void *data;
  struct _NodeList *next;
} NodeList;

struct _List
{
  NodeList *last;
};

/*Private function*/

NodeList *new_node(void *e)
{
  NodeList *n = NULL;

  n = (NodeList *)calloc(1, sizeof(NodeList));

  if (!n)
  {
    return NULL;
  }

  n->data = e;
  n->next = NULL;

  return n;
}

List *list_new()
{
  List *l = NULL;

  l = (List *)calloc(1, sizeof(List));

  if (!l)
  {
    return NULL;
  }

  l->last = NULL;

  return l;
}

Bool list_isEmpty(const List *pl)
{
  if (!pl)
  {
    return TRUE;
  }

  if (pl->last == NULL)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

Status list_pushFront(List *pl, void *e)
{
  NodeList *new_nd = NULL /*, *aux = NULL*/;

  if (!pl || !e)
  {
    return ERROR;
  }

  new_nd = new_node(e);

  if (!new_nd)
  {
    return ERROR;
  }

  if (list_isEmpty(pl) == TRUE)
  {
    /*pl->last = new_nd;
    pl->last->next = pl->last;*/
    pl->last = new_nd->next = new_nd;
  }
  else
  {
    new_nd->next = pl->last->next;
    pl->last->next = new_nd;
  }

  /*aux = pl->last->next;
  pl->last->next = new_nd;
  new_nd->next = aux;*/

  return OK;
}

Status list_pushBack(List *pl, void *e)
{
  NodeList *new_nd = NULL /*, *aux = NULL, *aux2 = NULL*/;

  if (!pl || !e)
  {
    return ERROR;
  }

  new_nd = new_node(e);

  if (!new_nd)
  {
    return ERROR;
  }

  if (list_isEmpty(pl) == TRUE)
  {
    /*pl->last = new_nd;
    pl->last->next = pl->last;*/
    pl->last = new_nd->next = new_nd;
  }
  else
  {
    new_nd->next = pl->last->next;
    pl->last->next = new_nd;
    pl->last = new_nd;
  }

  /*aux = pl->last;
  aux2 = pl->last->next;
  pl->last = new_nd;
  aux->next = new_nd;
  new_nd->next = aux2;*/

  return OK;
}

Status list_pushInOrder(List *pl, void *e, P_ele_cmp f, int order)
{
  NodeList *aux = NULL, *new_nd = NULL;
  if (!pl || !e || order == 0)
  {
    return ERROR;
  }

  new_nd = new_node(e);
  if (!new_nd)
  {
    return ERROR;
  }

  if (list_isEmpty(pl) == TRUE)
  {
    pl->last = new_nd->next = new_nd;
  }

  aux = pl->last;

  if (order > 0)
  {
    if (f(e, aux) > 0)
    {

      new_nd->next = pl->last->next;
      pl->last->next = new_nd;
      pl->last = new_nd;

      return OK;
    }

    while (f(e, aux->next->data) > 0)
    {
      aux = aux->next;
    }

    new_nd->next = aux->next;
    aux->next = new_nd;

    return OK;
  }
  else
  {
    if (f(e, aux) < 0)
    {
      new_nd->next = pl->last->next;
      pl->last->next = new_nd;
      pl->last = new_nd;

      return OK;
    }

    while (f(e, aux->next->data) < 0)
    {
      aux = aux->next;
    }

    new_nd->next = aux->next;
    aux->next = new_nd;

    return OK;
  }
}

void *list_popFront(List *pl)
{
  NodeList *aux1 = NULL /*, *aux2 = NULL*/;
  void *e;

  if (!pl || list_isEmpty(pl) == TRUE)
  {
    return NULL;
  }

  e = pl->last->next->data;
  if (pl->last->next == pl->last)
  {
    free(pl->last);
    pl->last = NULL;
    return e;
  }

  aux1 = pl->last->next->next;
  free(pl->last->next);
  pl->last->next = aux1;

  /*aux1 = pl->last->next->next;
  aux2 = pl->last->next;
  pl->last->next = aux1;
  e = aux2->data;

  free(aux2);*/

  return e;
}

void *list_popBack(List *pl)
{
  NodeList *aux1 = NULL /*, *aux2 = NULL*/;
  void *e;

  if (!pl || list_isEmpty(pl) == TRUE)
  {
    return NULL;
  }

  e = pl->last->data;

  if (pl->last->next == pl->last)
  {
    free(pl->last);
    pl->last = NULL;
    return e;
  }

  aux1 = pl->last->next;

  while (aux1->next != pl->last)
  {
    /*aux2 = aux1;*/
    aux1 = aux1->next;
  }

  aux1->next = pl->last->next;
  free(pl->last);
  pl->last = aux1;

  /*pl->last = aux2;
  aux2->next = aux1->next;
  e = aux1->data;
  free(aux1);*/

  return e;
}

void list_free(List *pl)
{
  NodeList *aux1 = pl->last->next, *aux2 = NULL;

  while (aux1)
  {
    aux2 = aux1;
    aux1 = aux1->next;
    free(aux2);
  }

  free(pl);
}

size_t list_size(const List *pl)
{
  NodeList *aux = NULL;
  long count = 0;

  if (!pl)
  {
    return -1;
  }

  if (list_isEmpty(pl) == TRUE)
  {
    return count;
  }

  aux = pl->last->next;

  while (aux != pl->last)
  {
    count++;
    aux = aux->next;
  }

  count++;

  return count;
}

int list_print(FILE *fp, const List *pl, P_ele_print f)
{
  NodeList *aux = NULL;
  int num_characters = 0, count = list_size(pl), i;

  if (!pl || !fp)
  {
    return -1;
  }

  fprintf(stdout, "SIZE: %ld\n", list_size(pl));
  aux = pl->last->next;

  for (i = 0; i < count; i++)
  {
    num_characters += f(fp, aux->data);
    aux = aux->next;
  }

  fprintf(fp, "\n");

  return num_characters;
}