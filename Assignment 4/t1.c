#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "t1.h"

Graph *create_graph(int num_nodes){
	Graph *g=(Graph*)(malloc(sizeof(Graph)));

	if(g==NULL) return NULL;

	g->totalVertices=num_nodes;
	
	g->adjList=(node**)(malloc(num_nodes*sizeof(node)));

	for(int i=0;i<num_nodes;i++){
		g->adjList[i] = (node*)(malloc(num_nodes*sizeof(node)));
		g->adjList[i]->numNbr=0;
		g->adjList[i]->nbr=NULL;
	}

	return g;
}

int compareIntegers(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void add_edge(Graph *g,int from,int to){
	int presentNeighbors = g->adjList[from]->numNbr; // this returns 0 if no element is present

	if(g->adjList[from]->nbr==NULL){
		g->adjList[from]->nbr=(int*)(malloc(sizeof(int)));
		g->adjList[from]->nbr[0]=to;
		g->adjList[from]->numNbr=1;
	} else{
		g->adjList[from]->nbr=realloc(g->adjList[from]->nbr,(presentNeighbors+1)*sizeof(int));
		g->adjList[from]->nbr[presentNeighbors]=to;
		g->adjList[from]->numNbr+=1;


		// keep sorting the neighbors array by the numbers
		qsort(g->adjList[from]->nbr,g->adjList[from]->numNbr,sizeof(int),compareIntegers);
	}
}

void bfs(Graph *g,int origin){
	bool *visited = (bool *)malloc(g->totalVertices * sizeof(bool));

    for (int i = 0; i < g->totalVertices; ++i) {
        visited[i] = false;
    }

    // Create a queue for BFS
    int *queue = (int *)malloc(g->totalVertices * sizeof(int));
    int front = -1, rear = -1;

    // Enqueue the origin onto the queue
    queue[++rear] = origin;
    visited[origin] = true;
	
	printf("BFS");

    // Perform BFS using a queue
    while (front != rear) {
        // Dequeue a vertex from the queue
        int currentVertex = queue[++front];
        printf("  %c", currentVertex+'A');

        // Enqueue adjacent vertices onto the queue that have not been visited
        for (int i = 0; i < g->adjList[currentVertex]->numNbr; ++i) {
            int neighbor = g->adjList[currentVertex]->nbr[i];
            if (!visited[neighbor]) {
                queue[++rear] = neighbor;
                visited[neighbor] = true;
            }
        }
    }

    // Free the memory allocated for the queue and visited array
    free(queue);
    free(visited);
	printf(" \n");
}

void dfsRecursive(Graph *g, int vertex, bool *visited) {
    visited[vertex] = true;
    printf(" %c ", vertex+'A');

    for (int i = 0; i < g->adjList[vertex]->numNbr; ++i) {
        int neighbor = g->adjList[vertex]->nbr[i];
        if (!visited[neighbor]) {
            dfsRecursive(g, neighbor, visited);
        }
    }
}

void dfs(Graph *g, int origin) {
    bool *visited = (bool *)malloc(g->totalVertices * sizeof(bool));

    for (int i = 0; i < g->totalVertices; ++i) {
        visited[i] = false;
    }

	printf("DFS:");
    dfsRecursive(g, origin, visited);
	printf("\b\n");

    free(visited);
}

void delete_graph(Graph *g){
	for(int i=0;i<g->totalVertices;i++){
		free(g->adjList[i]->nbr);
		free(g->adjList[i]);
	}
	free(g->adjList);

	free(g);
}
