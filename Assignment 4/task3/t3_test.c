#include <stdio.h>
#include <stdlib.h>

#include "task3.c"

int main(int argc,char *argv[]){
	if(argc<3){
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if(!load_vertices(argv[1])){
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if (!load_edges(argv[2])){
		printf("Failed to load edges\n");		
		return EXIT_FAILURE;
	}

	printf("Enter a stop number:");
	int stop;
	scanf("%d",&stop);

	vertex *bus = vertices[stop+1];

	printf("Bus stop number:%d\n",bus->stopId);
	printf("Stop name:%s\n",bus->name);
	printf("Latitude:%f\n",bus->latitude);
	printf("Longitude:%f\n",bus->longitude);

    /* get the start and end point
    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode);

	shortest_path(startingNode, endingNode);

	free_memory();
	*/

	return EXIT_FAILURE;
}
