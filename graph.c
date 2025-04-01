#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VTX 4096
#define MAX 100
#define MAX_LINE 80

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

Vertex *graph_get_vertex_from_id(Graph *g, long id);

Vertex *graph_get_vertex_from_id(Graph *g, long id)
{
    Vertex *vertex = NULL;
    int i, num;

    if (!g)
    {
        return NULL;
    }

    num = graph_getNumberOfVertices(g);

    for (i = 0; i < num; i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            vertex = g->vertices[i];
        }
    }

    if (!vertex)
    {
        return NULL;
    }

    return vertex;
}

/*----------------------------------------------------------------------------------------*/

Graph *graph_init()
{
    Graph *gr = NULL;

    gr = (Graph *)calloc(1, sizeof(Graph));

    if (!gr)
    {
        return NULL;
    }

    return gr;
}
Status graph_readFromFile(FILE *fin, Graph *g)
{
    int i, orig, dest, n_vertices;
    char line[MAX_LINE];

    if (!g || !fin)
    {
        return ERROR;
    }

    if (!fgets(line, MAX_LINE, fin))
    {
        return ERROR;
    }

    if (sscanf(line, "%d", &n_vertices) != 1)
    {
        return ERROR;
    }

    if (n_vertices <= 0)
    {
        return ERROR;
    }

    for (i = 0; i < n_vertices; i++)
    {
        if (!fgets(line, MAX_LINE, fin))
        {
            return ERROR;
        }
        if (!graph_newVertex(g, line))
        {
            return ERROR;
        }
        vertex_set_index(g->vertices[i], i);
    }

    while (fgets(line, MAX_LINE, fin) != NULL)
    {
        if (sscanf(line, "%d%d", &orig, &dest) != 2)
        {
            return ERROR;
        }

        if (!graph_newEdge(g, orig, dest))
        {
            return ERROR;
        }
    }

    return OK;
}
void graph_free(Graph *g)
{
    if (g)
    {
        for (int i = 0; i < g->num_vertices; i++)
        {
            vertex_free(g->vertices[i]);
        }
        free(g);
    }
}
int graph_getNumberOfVertices(const Graph *g) { return g->num_vertices; }
int graph_getNumberOfEdges(const Graph *g) { return g->num_edges; }
Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *v = NULL;
    long id;
    if (!g || !desc)
    {
        return ERROR;
    }

    v = vertex_initFromString(desc);
    if (!v)
    {
        return ERROR;
    }

    id = vertex_getId(v);

    if (graph_contains(g, id) == TRUE)
    {
        return OK;
    }

    g->vertices[g->num_vertices] = v;
    vertex_set_index(g->vertices[g->num_vertices], g->num_vertices);
    g->num_vertices++;

    return OK;
}
Status graph_newEdge(Graph *g, long orig, long dest)
{
    if (!g)
    {
        return ERROR;
    }

    if (graph_connectionExists(g, orig, dest) == TRUE)
    {
        return OK;
    }
    else
    {
        g->connections[orig][dest] = 1;
        g->num_edges++;
    }

    return OK;
}
Bool graph_contains(const Graph *g, long id)
{
    int i;

    if (!g)
    {
        return FALSE;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            return TRUE;
        }
    }

    return FALSE;
}
Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    if (!g)
    {
        return FALSE;
    }

    if (g->connections[orig][dest] == 1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int count = 0, i;
    if (!g)
    {
        return -1;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE)
        {
            count++;
        }
    }

    return count;
}
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i, j, count = 0;
    long id;

    if (!g)
    {
        return -1;
    }

    i = 0;

    while (strcmp(vertex_getTag(g->vertices[i]), tag) != 0)
    {
        i++;
    }

    id = vertex_getId(g->vertices[i]);

    for (j = 0; j < g->num_vertices; j++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[j])) == TRUE)
        {
            count++;
        }
    }

    return count;
}
long *graph_getConnectionsFromId(const Graph *g, long id)
{
    long *ids = NULL;
    int count = 0, i, j;

    if (!g)
    {
        return NULL;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE)
        {
            count++;
        }
    }

    ids = (long *)calloc(count, sizeof(long));

    if (!ids)
    {
        return NULL;
    }

    for (i = j = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE)
        {
            ids[j] = vertex_getId(g->vertices[i]);
            j++;
        }
    }

    return ids;
}
long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    long *ids = NULL, id;
    int count = 0, i, j;

    if (!g || !tag)
    {
        return NULL;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (strcmp(vertex_getTag(g->vertices[i]), tag) == 0)
        {
            id = vertex_getId(g->vertices[i]);
            break;
        }
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE)
        {
            count++;
        }
    }

    ids = (long *)calloc(count, sizeof(long));
    if (!ids)
    {
        return NULL;
    }

    for (i = j = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE)
        {
            ids[j++] = vertex_getId(g->vertices[i]);
        }
    }

    return ids;
}
int graph_print(FILE *pf, const Graph *g)
{
    int count = 0, i, j;

    if (!pf || !g)
    {
        return -1;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        count += vertex_print(pf, g->vertices[i]);

        count += fprintf(stdout, " : ");

        for (j = 0; j < graph_getNumberOfVertices(g); j++)
        {
            if (graph_connectionExists(g, vertex_getId(g->vertices[i]), vertex_getId(g->vertices[j])))
            {
                count += vertex_print(pf, g->vertices[j]);
            }
        }
        count += fprintf(pf, "\n");
    }

    return count;
}

Status graph_depthSearch(Graph *g, long vf, long vt)
{
    Stack *s = NULL;
    Status st = OK;
    Vertex *vo = NULL, *Vf = NULL, *Vt = NULL, *v_aux = NULL;
    long *vertex_connect = NULL;
    int i, num_connections;

    if (!g || vf < 0 || vt < 0)
    {
        return ERROR;
    }

    Vf = graph_get_vertex_from_id(g, vf);

    if (!Vf)
    {
        return ERROR;
    }

    Vt = graph_get_vertex_from_id(g, vt);

    if (!Vt)
    {
        return ERROR;
    }

    if (graph_contains(g, vf) == FALSE)
    {
        return ERROR;
    }

    if (graph_contains(g, vt) == FALSE)
    {
        return ERROR;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (vertex_setState(g->vertices[i], WHITE) == ERROR)
        {
            return ERROR;
        }
    }

    st = OK;

    s = stack_init();

    if (!s)
    {
        return ERROR;
    }

    if (vertex_setState(Vf, BLACK) == ERROR)
    {
        stack_free(s);
        return ERROR;
    }

    if (stack_push(s, Vf) == ERROR)
    {
        stack_free(s);
        return ERROR;
    }

    while (stack_isEmpty(s) == FALSE && st == OK)
    {
        vo = stack_pop(s);
        if (!vo)
        {
            st = ERROR;
            break;
        }
        

        vertex_print(stdout, vo);
        fprintf(stdout, "\n");

        if (vertex_cmp(vo, Vt) == 0)
        {
            st = OK;
            break;
        }

        vertex_connect = graph_getConnectionsFromId(g, vertex_getId(vo));
        num_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(vo));

        if (!vertex_connect)
        {
            st = ERROR;
            break;
        }

        for (i = 0; i < num_connections; i++)
        {
            v_aux = graph_get_vertex_from_id(g, vertex_connect[i]);

            if (!v_aux)
            {
                st = ERROR;
                break;
            }

            if (vertex_getState(v_aux) == WHITE)
            {
                if (vertex_setState(v_aux, BLACK) == ERROR || stack_push(s, v_aux) == ERROR)
                {
                    st = ERROR;
                    break;
                }
            }
        }
        
        free(vertex_connect);
    }

    stack_free(s);
    return st;
}