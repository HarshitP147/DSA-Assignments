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

	// whenever we are encountered with quotes, it still follows the ignoration logic should not be happening

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

// here we sort the games as per there score

void merge(game arr[],int left,int mid,int right){
	int n1=mid-left+1,n2=right-mid;

	game arr1[n1],arr2[n2]; // array of structs
	
	int i=0,j=0;
	// filling up the separated arrays
	for(;i<n1;i++){
		copyStructGameData(&arr1[i],&arr[left+i]);
		// arr1[i]=arr[left+i];
	}
	for(;j<n2;j++){
		copyStructGameData(&arr2[j],&arr[mid+j+1]);
		// arr2[j]=arr[mid+j+1];
	}

	i=0,j=0;
	int k=left;
	// now adding them back the ascending order
	while(i!=n1 && j!=n2){
		if(arr1[i].score>arr2[j].score){
			copyStructGameData(&arr[k],&arr1[i]);
			// arr[k]=arr1[i];
			i++;
		}
		else{
			copyStructGameData(&arr[k],&arr2[j]);
			// arr[k]=arr2[j];
			j++;
		}
		k++;
	}
	
	// add the remaining elements if are any left
	while(i<n1){
		copyStructGameData(&arr[k],&arr1[i]);
		// arr[k]=arr1[i];
		i++,k++;
	}
	while(j<n2){
		copyStructGameData(&arr[k],&arr2[j]);
		// arr[k]=arr2[j];
		j++,k++;
	}
}

void mergeSort(game arr[],int left,int right){
	if(left<right){
		int mid = (left+right)/2;
		mergeSort(arr,left,mid);
		mergeSort(arr,mid+1,right);

		merge(arr,left,mid,right);
	}
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
	mergeSort(GameArray,0,arrayIndex-1);

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
