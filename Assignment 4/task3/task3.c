#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "t3.h"

#define MAX_LEN	50

typedef struct vertex vertex;
struct vertex{
	int stopId;
	char *name;
	double latitude;
	double longitude;
} *vertices[8000];

int nStops=0;

// loads the edges from the CSV file of name fname
int load_edges(char *fname){
	FILE *csv = fopen(fname,"r");

	if(csv==NULL) return 0;


	return 1;
}

// loads the vertices from the CSV file of name fname
int load_vertices(char *fname){
	FILE *csv = fopen(fname,"r");

	if(csv==NULL) return 0;

	char *buffer = (char*)(malloc(MAX_LEN*sizeof(char)));
	if(buffer==NULL) return 0;

	int x=1;
	bool inQuotes=false;

	buffer=fgets(buffer,MAX_LEN,csv);
	
	char *data = (char*)(malloc(MAX_LEN*sizeof(char)));
	if(data==NULL) return 0;

	int k=0;

	do{
		// create a node for the bus stop
		vertex *busStop = (vertex*)(malloc(sizeof(vertex)));

		busStop->name=(char*)(malloc(MAX_LEN*sizeof(char)));

		if(busStop==NULL || busStop->name==NULL) return 0;

		char c;
		int fieldIndex=0;

		char *fieldData=(char*)(malloc(MAX_LEN*sizeof(char)));
		int x=0;

		for(int i=0;i<strlen(buffer);i++){
			c=buffer[i];

			if(c=='"') continue;

			else if(c==','){
				// this is adding the comma which we do not want

				switch(fieldIndex){
					case 0:
						busStop->stopId=atoi(fieldData);
						printf("Stop number:%d\n",busStop->stopId);
						break;
					case 1:
						strcpy(busStop->name,fieldData);
						printf("Stop name:%s\n",busStop->name);
						break;
					case 2:
						busStop->latitude=atof(fieldData);
						printf("Latitude:%f\n",busStop->latitude);
						break;
					case 3:
						busStop->latitude=atof(fieldData);
						printf("Longitude:%f\n",busStop->longitude);
						break;
				}

				// clear the buffer and reset the data
				fieldData=(char*)(malloc(MAX_LEN*sizeof(char)));
				x=0;
				fieldIndex+=1;
			}

			else{
				fieldData[x++]=c;
			}
		}
		printf("\n");

		vertices[nStops++] = busStop;
		
		
		buffer=fgets(buffer,MAX_LEN,csv);
	}while(buffer!=NULL);

	
	return 1;
}

// prints the shortest path between startNode and endNode, if there is any
void shortest_path(int startNode,int endNode){

}

// frees any memory that was used
void free_memory(void){

}
