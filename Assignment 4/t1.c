#include <stdio.h>
#include <stdlib.h>

#include "t1.h"

Graph *create_graph(int num_nodes){
	Graph *g;

	g=(Graph*)(malloc(sizeof(Graph)));

	g->totalVertices=num_nodes;

	for(int i=0;i<num_nodes;i++){
		g->adjList[i]=(node*)(malloc(num_nodes*sizeof(int)));
		g->adjList[i]->nbr=(int*)(malloc(num_nodes*sizeof(int)));
		g->adjList[i]->numNbr=0;
		g->adjList[i]->nbr[0]=-1;
	}

	return g;
}

void add_edge(Graph *g,int from,int to){
	int len=0,i=0;

	while(g->adjList[from]->nbr[i]!=-1){
		i++;
		len++;
	}

	g->adjList[from]->nbr=(int*)(realloc(g->adjList[from]->nbr,(++len)*sizeof(int)));
	g->adjList[from]->numNbr++;
	g->adjList[from]->nbr[len-1]=to;

}

void bfs(Graph *g,int origin){

}

void dfs(Graph *g,int origin){
	static int visited[26]={0};
	
	if(visited[origin]){
		return;
	} else{
		visited[origin]=1;
		printf("%d ",origin);

		int i=0;
		while(i<g->adjList[origin]->numNbr){
			int nbr=g->adjList[origin]->nbr[i];
			dfs(g,nbr);
			i++;
		}
	}
}

void delete_graph(Graph *g){

	for(int i=0;i<g->totalVertices;i++){
		free(g->adjList[i]);
		free(g->adjList[i]->nbr);
	}

	free(g);
}
