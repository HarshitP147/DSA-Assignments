#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 59
#define MAX_STRING_SIZE 20

int collisions=0;

typedef struct Element Element;
struct Element{
	char *name;
	int freq;
} *HashTable[ARRAY_SIZE] = {NULL};

int hash1(char *s){
	int hash=0;
	while(*s){
		hash=(hash+*s-'A')%ARRAY_SIZE;
		s++;
	}
	return hash;
}

Element *searchHashTable(char *name){
	Element *ele;
	int hashValue=hash1(name);

	while(HashTable[hashValue]!=NULL){
		if(!strcmp(HashTable[hashValue]->name,name)){
			ele=HashTable[hashValue];
			return ele;
		}
		// this is for linear probing
		hashValue=(hashValue+1)%ARRAY_SIZE;
	}
	return NULL;
}

void appendHashTable(char *name){
	Element *new=searchHashTable(name);
	
	if(new!=NULL){
		new->freq++;
		return;
	}

	// creating a new element
	Element *newElement=(Element*)(malloc(sizeof(Element)));
	newElement->freq=1;
	newElement->name=(char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
	strcpy(newElement->name,name);

	int index=hash1(name);

	while(HashTable[index]!=NULL){
		// this is for linear probing
		index=(index+1)%ARRAY_SIZE;
		collisions++;
	}
	HashTable[index]=newElement;
}

void fileLoader(FILE *csv){
	char *buffer=(char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
	int len=MAX_STRING_SIZE;

	while(fgets(buffer,MAX_STRING_SIZE,csv)){
		if(len>0 && buffer[strlen(buffer)-1]=='\n'){
			len=strlen(buffer)-2;
			buffer[len]='\0';
		} else{
			len=strlen(buffer);
		}
		appendHashTable(buffer);
	}

	free(buffer);
}


int main(int argc,char **argv){
	float terms=0;
	FILE *csv=fopen(argv[1],"r");

	if(csv==NULL){
		printf("Error:Could not open the file.\n");
		return -1;
	}

	fileLoader(csv);

	printf("File %s loaded\n",argv[1]);
	printf(" Capacity: %d\n",ARRAY_SIZE);

	int hashValue;
	for(int i=0;i<ARRAY_SIZE;i++){
		if(HashTable[i]!=NULL) {
			// printf("Name:%s Freq:%d\n",HashTable[i]->name,HashTable[i]->freq);
			terms++;
		} else{
			// printf("NULL\n");
		}
	}


	printf(" Num Terms: %0.0f\n",terms);
	printf(" Collisions: %d\n",collisions);
	float loadFactor=terms/ARRAY_SIZE;
	printf(" Load: %f\n",loadFactor);


	Element *cur=(Element*)(malloc(sizeof(Element)));
	char *userInput=(char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
	printf("Enter term to get frequency or type \"%s\" to escape\n","quit");
	while(1){
		printf(">>> ");
		gets(userInput);

		if(strcmp(userInput,"quit")==0){
			break;
		}
		cur=searchHashTable(userInput);
		if(cur!=NULL){
			printf("%s - %d \n",userInput,cur->freq);
		} else{
			printf("%s - 0 \n",userInput);
		}
	}
	free(cur);
	free(userInput);

	fclose(csv);

	return 0;
}
