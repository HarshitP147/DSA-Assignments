#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "t3.h"

#define MAX_LEN 75

// using adjacency list for representing the graph
typedef struct Vertex stop;
struct Vertex{
	int stopId;
	char *name;
	float latitude;
	float longitude;
} stops[8000];

typedef struct EdgeBufferData{
	int vertex1;
	int vertex2;
	int weight;
} edgeBufferData;

typedef struct Destination{
	int stopId;
	int cost;
} destination;

typedef struct Route{
	int stopId;
	destination *stops;
} route;

typedef struct city{
	route *routes;	
} city;
city *dublinBus;

int size=1;

stop extracVertextBufferData(char *buffer){
	char c;

	char *fieldData=(char*)(malloc(MAX_LEN*sizeof(char)));
	int x=0;

	int fieldIndex=1;

	stop busStop;
	busStop.stopId=0;
	busStop.name=(char*)(malloc(MAX_LEN*sizeof(char)));
	busStop.latitude=0;
	busStop.longitude=0;

	for(int i=0;i<strlen(buffer);i++){
		c=buffer[i];

		if(c=='"')  continue;
		if(c==','){
			switch(fieldIndex){
				case 1:
					busStop.stopId=atoi(fieldData);
					break;

				case 2:
					strcpy(busStop.name,fieldData);
					break;

				case 3:
					busStop.latitude=atof(fieldData);
					break;
			}
			
			x=0;
			fieldData=(char*)(malloc(MAX_LEN*sizeof(char)));
			fieldIndex++;
		}
		else{
			fieldData[x++]=c;
		}
	}
	if(fieldIndex==4){
		busStop.longitude=atof(fieldData);
	}

	return busStop;
}

int load_vertices(char *fname){
	FILE *csv = fopen(fname,"r");

	if(csv==NULL) return 0;

	int k=0;  // counter for the stops array
	char *buffer = (char*)(malloc(MAX_LEN*sizeof(char)));

	char c; // to read each of the character
	
	// this is to avoid the first line
	while(c!='\n') c=fgetc(csv);

	stop busStop;

	while(fgets(buffer,MAX_LEN,csv)){
		busStop=extracVertextBufferData(buffer);	
		stops[k++]=busStop;
	}

	return 1;
}

void extractEdgeBufferData(char *buffer){
	char c;

	char *fieldData=(char*)(malloc(MAX_LEN*sizeof(char)));
	int x=0;

	int fieldIndex=1;

	edgeBufferData temp;

	for(int i=0;i<strlen(buffer);i++){
		c=buffer[i];
		if(c=='"') continue;
		else if(c==','){
			switch(fieldIndex){
				case 1:
					temp.vertex1=atoi(fieldData);
					break;

				case 2:
					temp.vertex2=atoi(fieldData);
					break;
			}
			
			fieldIndex++;
			fieldData=(char*)(malloc(MAX_LEN*sizeof(char)));
			x=0;
		}
		else{
			fieldData[x++]=c;
		}
	}

	if(fieldIndex==3){
		temp.weight=atoi(fieldData);
	}

	// now the real insertion of takes here

	for(int i=0;i<size;i++){
		if((temp.vertex1==dublinBus->routes[i].stopId) || (temp.vertex2==dublinBus->routes[i].stopId)){
			int numberStops = sizeof(dublinBus->routes[i].stops)/sizeof(dublinBus->routes[i].stops[0]);
			
			// reallocate the previous size
			dublinBus->routes[i].stops=(destination*)(realloc(dublinBus->routes[i].stops,(++numberStops)*sizeof(destination)));


			// check which one is the current equivalent stop


			// dublinBus->routes[i].stops[numberStops]={,};
		}
	}

}

int load_edges(char *fname){
	FILE *csv = fopen(fname,"r");

	if(csv==NULL) return 0;

	char c;
	while(c!='\n') c=fgetc(csv);

	// allocate the size for the adjacency list
	dublinBus=(city*)(malloc(sizeof(city)));
	size_t routeSize = sizeof(route);
	dublinBus->routes=(route*)(malloc(routeSize));

	char *buffer = (char*)(malloc(MAX_LEN*sizeof(char)));

	while(fgets(buffer,MAX_LEN,csv)){
		extractEdgeBufferData(buffer);	
		dublinBus->routes=(route*)(realloc(dublinBus->routes,(++size)*sizeof(route)));
	}

	
	return 1;
}
