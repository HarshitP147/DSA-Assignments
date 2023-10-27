#include <stdio.h>
#include <stdlib.h>

typedef struct Game game;
struct Game{
	char *title;
	char *platform;
	int score;
	int releaseYear;
};

int next_field(FILE *csv,char *buffer,int max_len){
	int r_value,i=0,firstline=1,inside_quotes=0;
	char c;
	while(!feof(csv)){
		c = fgetc(csv);
		if(c=='#') firstline=1;
		if(c=='"') continue;
		if(c=='\n') firstline=0;
		if(!firstline){
			if(c==',' || c=='\n' || feof(csv)){
				buffer[i++] = '\0';
				(c==',') ? printf("%s \n",buffer) : printf("%s\n\n",buffer);
				r_value = c==',' ? 0 : 1;
				i=0;
				buffer=(char*)(malloc(max_len));
				continue;
			}
			buffer[i++] = c;
		}
	}
	return r_value;
}

int main(int argc,char *argv[]){
	FILE *csv;
	csv = fopen(argv[1],"r");

	if(csv==NULL){
		printf("Error:Could not open the file\n");
		return -1;
	}

	int max_len=1000000;
	char *buffer=(char*)(malloc(max_len));

	int value = next_field(csv,buffer,max_len);

	do{
		value = next_field(csv,buffer,max_len);
	}while(!feof(csv));

	free(buffer);
	fclose(csv);

	return 0;
}
