#include <stdio.h>
#include <stdlib.h>

#include "t1.h"
#include "t1.c"

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

void adjList(Graph *g){
	for(int i=0;i<g->totalVertices;i++){
		printf("%c : ",i+'A');
		for(int j=0;j<g->adjList[i]->numNbr;j++){
			printf("%c ",g->adjList[i]->nbr[j]+'A');
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
    int num_nodes = 6;
	Graph *graph=create_graph(num_nodes);

    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));

	adjList(graph);
	
	dfs(graph,char2val('A'));
	bfs(graph,char2val('A'));
	
    delete_graph(graph);
	
	return 0;
}
