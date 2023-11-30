#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "t2.h"

Graph *create_graph(int num_nodes){
	Graph *g;

	g=(Graph*)(malloc(sizeof(Graph)));

	if(g==NULL) return NULL;

	g->totalVertices=num_nodes;

	g->adjMat=(int**)(malloc(MAX_VERTICES*MAX_VERTICES*sizeof(int)));

	for(int i=0;i<num_nodes;i++){
		g->adjMat[i]=(int*)(malloc(MAX_VERTICES*sizeof(int)));
	}

	for(int i=0;i<num_nodes;i++){
		for(int j=0;j<num_nodes;j++){
			g->adjMat[i][j]=0;
		}
	}

	return g;
}

void add_edge(Graph *g,int from,int to, int weight){
	// adds an bidirectional weighted edge into the graph
	g->adjMat[from][to]=weight;
	g->adjMat[to][from]=weight;
}

typedef struct node node;
struct node{
	int key;
	int distance;
};

int compareIntegers(const void *a,const void *b){
	return (*(node*)a).distance > (*(node*)b).distance ;
}

void dijkstra(Graph *g,int origin){
	int totalVertices = g->totalVertices;
	 
    int* distance = (int*)malloc(totalVertices * sizeof(int));
    int* visited = (int*)malloc(totalVertices * sizeof(int));

    // Initialize distance and visited arrays
    for (int i = 0;i<totalVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance from the source vertex to itself is always 0
    distance[origin] = 0;

    // Find shortest path for all vertices
    for (int count = 0;count<totalVertices-1; count++) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        // Choose the minimum distance vertex from the set of vertices not yet processed
        for (int v = 0;v<totalVertices; v++) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        // Mark the picked vertex as processed
        visited[minIndex] = 1;

        // Update distance value of the adjacent vertices of the picked vertex
        for (int v = 0;v<totalVertices; v++) {
            if (!visited[v] && g->adjMat[minIndex][v] && distance[minIndex] != INT_MAX &&
                distance[minIndex] + g->adjMat[minIndex][v] < distance[v]) {
                distance[v] = distance[minIndex] + g->adjMat[minIndex][v];
            }
        }
    }

	node *vertexOrder=(node*)(malloc(totalVertices*sizeof(node)));
	for(int i=0;i<totalVertices;i++){
		vertexOrder[i].key=i;
		vertexOrder[i].distance=distance[i];
	}

	qsort(vertexOrder,totalVertices,sizeof(node),compareIntegers);

	for(int i=0;i<totalVertices;i++){
		printf("%c ",vertexOrder[i].key+'A');
	}
	printf("\n");
    for (int i = 0; i < totalVertices; i++) {
		printf("The length of the shortest path between %c and %c is %d\n",origin+'A',i+'A',distance[i]);
    }

	free(vertexOrder);
    free(distance);
    free(visited);
}

void delete_graph(Graph *g){
	for(int i=0;i<g->totalVertices;i++){
		free(g->adjMat[i]);
	}
	free(g->adjMat);
	free(g);
}
