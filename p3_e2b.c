#include "graph.h"

int main(int argc, char *argv[]){
    char *filename=NULL;
    FILE *file=NULL;
    Graph *g=NULL;
    long id_origin, id_destination;

    if(argc < 4){
        fprintf(stderr, "Format should be: %s <File1> <ID_origin> <ID_destination> \n", argv[0]);
        return -1;
    }

    filename = argv[1];

    file=fopen(filename, "r");
    if(!file){
        return -1;
    }

    g=graph_init();
    if(!g){
        fclose(file);
    }

    if(graph_readFromFile(file, g)==ERROR){
        fclose(file);
        graph_free(g);
        return -1;
    }

    id_origin = strtol(argv[2], NULL, 10);
    id_destination = strtol(argv[3], NULL, 10);

    fprintf(stdout, "--------DFS--------\n");
    fprintf(stdout, "Input:\n");
    fprintf(stdout, "From Vertex id: %ld\n", id_origin);
    fprintf(stdout, "To Vertex id: %ld\n", id_destination);
    fprintf(stdout, "Output\n");
    if(graph_depthSearch(g, id_origin, id_destination)==ERROR){
        fclose(file);
        graph_free(g);
        return -1;
    }

    fprintf(stdout, "--------BFS--------\n");
    fprintf(stdout, "Input:\n");
    fprintf(stdout, "From Vertex id: %ld\n", id_origin);
    fprintf(stdout, "To Vertex id: %ld\n", id_destination);
    fprintf(stdout, "Output\n");
    if(graph_breadthSearch(g, id_origin, id_destination)==ERROR){
        fclose(file);
        graph_free(g);
        return -1;
    }

    fclose(file);
    graph_free(g);
    return 0;
}
