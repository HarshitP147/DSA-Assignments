#include <stdio.h>
#include <stdlib.h>

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

void sortArray(int **arr,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(*arr[i]>*arr[i+1]){
				int temp = *arr[i];
				*arr[i]=*arr[i+1];
				*arr[i+1]=temp;
			}
		}
	}
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
		for(int i=0;i<presentNeighbors;i++){
			for(int j=0;j<presentNeighbors;j++){
				if(g->adjList[from]->nbr[i]>g->adjList[from]->nbr[i+1]){
					int temp = g->adjList[from]->nbr[i];
					g->adjList[from]->nbr[i] = g->adjList[from]->nbr[i+1];
					g->adjList[from]->nbr[i+1] = temp;
				}
			}
		}
	}
}

void bfs(Graph *g,int origin){
	static int *visited=NULL;

	if(visited==NULL){
		visited=(int*){malloc(g->totalVertices*sizeof(int))};

		if(visited==NULL) return;

		for(int i=0;i<g->totalVertices;i++) visited[i]=0;
		printf("BFS : ");
	}

	if(visited[origin]){
		return;
	} else{
		visited[origin]=1;
		printf("%c ",origin+'A');

		for(int i=0;i<g->adjList[origin]->numNbr;i++){
			int nbr = g->adjList[origin]->nbr[i];
			bfs(g,nbr);
		}

	}
}

void dfs(Graph *g,int origin){
	static int *visited=NULL;

	if(visited==NULL){
		visited=(int*){malloc(g->totalVertices*sizeof(int))};

		if(visited==NULL) return;

		for(int i=0;i<g->totalVertices;i++) visited[i]=0;
		printf("DFS : ");
	}

	if(visited[origin]){
		return;
	} else{
		visited[origin]=1;

		for(int i=0;i<g->adjList[origin]->numNbr;i++){
			int nbr = g->adjList[origin]->nbr[i];
			dfs(g,nbr);
		}

		printf("%c ",origin+'A');
	}
}

void delete_graph(Graph *g){
	for(int i=0;i<g->totalVertices;i++){
		free(g->adjList[i]->nbr);
		free(g->adjList[i]);
	}

	free(g);
}
