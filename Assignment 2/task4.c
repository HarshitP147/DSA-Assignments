#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_len 250
#define ARRAY_SIZE 20000

typedef struct Game game;
struct Game{
	char *title,*platform;
	int score,releaseYear;
};

// function that extracts the buffer data into a struct
void extractBufferData(char *buffer){
	char c,*field=(char*)(malloc(max_len*sizeof(char)));
	int i=0,x=0,col=1;

	game GameInfo;

	GameInfo.title=(char*)(malloc(max_len*sizeof(char)));
	GameInfo.platform=(char*)(malloc(max_len*sizeof(char)));
	GameInfo.score=0;
	GameInfo.releaseYear=0;

	for(int i=0;i<strlen(buffer);i++){
		c=buffer[i];
		if(c==',' || c=='\n'){
			switch(col){
				case 1:
					strcpy(GameInfo.title,field);
					break;
				case 2:
					strcpy(GameInfo.platform,field);
					break;
				case 3:
					GameInfo.score=atoi(field);
					break;
				case 4:
					GameInfo.releaseYear=atoi(field);
					break;
			}
			col++;
			x=0;
			field=(char*)(malloc(max_len*sizeof(char)));
			continue;
		}
		field[x++]=c;
	}

	// the struct we declared at the start of the function now stores the value
	
	free(field);
}


void fileParser(FILE *csv){
	char c;
	char *buffer=(char*)(malloc(max_len*sizeof(char)));
	int len,x=0;

	while(c!='\n') c=fgetc(csv); // this way we have skipped the first line
	
	// we scan the entire the line and store it in the buffer
	while(fgets(buffer,max_len,csv)){
		extractBufferData(buffer);
	}
	free(buffer);
}

int main(int argc,char *argv[]){
	FILE *csv;
	csv = fopen(argv[1],"r");

	if(csv==NULL){
		printf("Error:Could not open the file\n");
		return -1;
	}

	fileParser(csv);

	fclose(csv);

	return 0;
}
