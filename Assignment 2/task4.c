#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_len 250
#define ARRAY_SIZE 20000

int arrayIndex=0;

typedef struct Game game;
struct Game{
	char *title,*platform;
	int score,releaseYear;
} GameArray[ARRAY_SIZE];

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
	GameArray[arrayIndex++]=GameInfo;
	
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
		buffer=(char*)(malloc(max_len*sizeof(char)));
	}
	free(buffer);
}

void copyStructGameData(game *dest,game *src){
	dest->platform=(char*)(malloc(max_len*sizeof(char)));
	dest->title=(char*)(malloc(max_len*sizeof(char)));

	strcpy(dest->title,src->title);
	strcpy(dest->platform,src->platform);
	dest->score=src->score;
	dest->releaseYear=src->releaseYear;
}


int main(int argc,char *argv[]){
	FILE *csv;
	csv = fopen(argv[1],"r");
	
	if(csv==NULL){
		printf("Error:Could not open the file\n");
		return -1;
	}

	fileParser(csv);

	// taking arrayIndex because that is the actual size of the array
	//mergeSortScore(GameArray,0,ARRAY_SIZE-1);

	game temp;
	
	for(int i=0;i<arrayIndex;i++){
		temp=GameArray[i];
		printf("Title:%s\n",temp.title);
		printf("Platform:%s\n",temp.platform);
		printf("Score:%d\n",temp.score);
		printf("Release year:%d\n\n",temp.releaseYear);
	}

	return 0;
}
