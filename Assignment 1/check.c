#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 20
#define ARRAY_SIZE 59

int hash(char *s){
    int hash=0,ascii;
    while(*s){
        hash=hash+(ascii<<2)%ARRAY_SIZE;
        s++;
    }
    return hash%ARRAY_SIZE;
}

void fileLoader(FILE *csv){
	char *buffer=(char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
	int len=MAX_STRING_SIZE;

	while(fgets(buffer,MAX_STRING_SIZE,csv)){
		if(len>0 && buffer[strlen(buffer)-1]=='\n'){
			len=strlen(buffer)-1;
			buffer[len]='\0';
		} else{
			len=strlen(buffer);
		}
        int hashValue = hash(buffer);
        printf("Name:%s Hash value:%d\n",buffer,hashValue);
	}

	free(buffer);
}

int main(){
    FILE *csv = fopen("names.csv","r");

    fileLoader(csv);

    fclose(csv);
    return 0;
}