#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 59
#define MAX_STRING_SIZE 20

int collisions=0;

typedef struct Person Person;
struct Person{
	int personId;
	char *depositionId;
	char *surname;
	char *forename;
	int freq;
	char *personType,*gender,*nationality,*religion,*occupation;
} *HashTable[ARRAY_SIZE] = {NULL};

int customHash(char *s){
	int hash=0;
	while(*s){
		hash=(hash+*s-'A')%ARRAY_SIZE;
		s++;
	}
	return hash;
}

int hash3(char *s){
	int hash=0;
	while(*s){
		hash=1+(hash+*s-'A')%(ARRAY_SIZE-1);
		s++;
	}
	return hash;
}

Person *searchHashTable(char *name){
	Person *ele;
	int h1=customHash(name),h2=hash3(name),i=0;

	int hashIndex = h1 + i*h2;

	while(HashTable[hashIndex]!=NULL){
		if(!strcmp(HashTable[hashIndex]->name,name)){
			ele=HashTable[hashIndex];
			return ele;
		}
		// this is for double hashing
		i++;
		hashIndex = (h1 + i*h2)%ARRAY_SIZE;
	}
	return NULL;
}

void appendHashTable(char *name){
	Person *new=searchHashTable(name);

	if(new!=NULL){
		new->freq++;
		return;
	}

	// creating a new element
	Person *newPerson=(Person*)(malloc(sizeof(Person)));
	newPerson->freq=1;
	newPerson->name=(char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
	strcpy(newPerson->name,name);

	int h1=customHash(name),h2=hash3(name),i=0;

	int hashIndex = h1 + i*h2;

	while(HashTable[hashIndex]!=NULL){
		// this is for double hashing
		i++;
		hashIndex = (h1 + i*h2)%ARRAY_SIZE;
		collisions++;
	}
	HashTable[hashIndex]=newPerson;
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
			terms++;
		}
	}


	printf(" Num Terms: %0.0f\n",terms);
	printf(" Collisions: %d\n",collisions);
	float loadFactor=terms/ARRAY_SIZE;
	printf(" Load: %f\n",loadFactor);


	Person *cur=(Person*)(malloc(sizeof(Person)));
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
