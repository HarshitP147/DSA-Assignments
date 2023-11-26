#ifndef T1_H_
#define T1_H_

typedef struct Node node;
struct Node{
	int key;
	int numNbr;
	int *nbr;
};

typedef struct Graph{
	int totalVertices;
	node **adjList;
} Graph;

Graph* create_graph(int num_nodes);
void add_edge(Graph *g, int from, int to);
void bfs(Graph* g, int origin);
void dfs(Graph* g, int origin);
void delete_graph(Graph *g);

#endif
