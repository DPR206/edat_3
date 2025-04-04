#include "graph.h"

int main(int argc, char *argv[]){
    char *filename=NULL;
    FILE *file=NILL;
    Graph *cities=NULL;
    Vertex *vf=NULL, *vt=NULL;

    if(argc < 4){
        printf(stderr, "Format should be: %s <File1> <From vertex> <To vertex> \n", argv[0]);
        return -1;
    }

    filename = argv[1];


    if(!file=fopen(filename, "r")){
        return -1;
    }

    if(graph_readFromFile(file, cities)==ERROR){
        fclose(file);
        return -1;
    }

    fprintf(stdout, "--------DFS--------\n");
    if(graph_depthSearch(cities, vf, vt)==ERROR){
        fclose(fich);
        return -1;
    }

    fprintf(stdout, "--------BFS--------\n");
    if(graph_breadthSearch(cities, vf, vt)==ERROR){
        fclose(fich);
        return -1;
    }

    return 0;
}
