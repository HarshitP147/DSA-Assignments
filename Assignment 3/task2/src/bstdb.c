#include "bstdb.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 75

typedef struct DbNode DbNode;
struct DbNode{
	int bookId;
	char *name;
	int wordCount;
	char *author;

	DbNode *left;
	DbNode *right;
} *dbRoot;

int num_search;
int num_comp;

int *bookIdRecs;
int x;
int k;

// utility function to get maximum out of two numbers
int max(int x,int y){
	return (x>y) ? x : y;
}

int bookIdSearch(int id,int left,int right){
	int mid=(left+right)/2;

	int retValue=-1;

	while(left<right){
		if(id==bookIdRecs[mid]){
			retValue=mid;
			break;
		}
		else if(id<bookIdRecs[mid]){
			right=mid-1;
		}
		else if(id>bookIdRecs[mid]){
			left=mid+1;
		}
		else{
			break;
		}
	}

	return retValue;
}

DbNode *initializeNode(void){
	DbNode *newRec=(DbNode*)(malloc(sizeof(DbNode)));

	newRec->name=(char*)(malloc(MAX_LEN*sizeof(char)));
	newRec->author=(char*)(malloc(MAX_LEN*sizeof(char)));

	newRec->bookId=0;
	newRec->wordCount=0;
	
	newRec->left=NULL;
	newRec->right=NULL;

	return newRec;
}

int
bstdb_init ( void ) {
	dbRoot=NULL;

	num_search=0;
	num_comp=0;

	bookIdRecs=(int*)(malloc(500000*sizeof(int)));
	x=0;

	for(int i=0;i<500000;i++){
		bookIdRecs[i]=i+1;
		x++;
	}

	srand(time(NULL));
	for(int i=x-1;i>0;i--){
		int j=rand()%(i+1);
		int temp=bookIdRecs[i];
		bookIdRecs[i]=bookIdRecs[j];
		bookIdRecs[j]=temp;
	}

	k=0;

	return 1;
}

void addNewNode(DbNode **root,DbNode **newNode){
	if((*root)==NULL){
		(*root)=(*newNode);
		return;
	} else if((*newNode)->bookId<(*root)->bookId){
		addNewNode(&(*root)->left,&(*newNode));
	} else{
		addNewNode(&(*root)->right,&(*newNode));
	}
	
}

int
bstdb_add ( char *name, int word_count, char *author ) {
	DbNode *newNode=initializeNode();

	if(newNode==NULL) return -1;

	newNode->bookId=bookIdRecs[k++];

	newNode->name=name;
	newNode->author=author;
	
	newNode->wordCount=word_count;

	if(dbRoot==NULL){
		dbRoot=newNode;
	} else{
		addNewNode(&dbRoot,&newNode);
	}

	return newNode->bookId;
}

DbNode *searchNode(DbNode **root,int docId){
	num_search++;
	DbNode *search=*root;

	while(1){
		if(docId<search->bookId){
			search=search->left;
		}
		else if(docId==search->bookId){
			break;
		}
		else if(docId>search->bookId){
			search=search->right;
		}
		else{
			search=NULL;
			break;
		}
		num_comp+=4;
	}

	return search;
}

int
bstdb_get_word_count ( int doc_id ) {
	DbNode *search = searchNode(&dbRoot,doc_id);

	return (search==NULL) ? -1 : search->wordCount;
}

char*
bstdb_get_name ( int doc_id ) {
	DbNode *search = searchNode(&dbRoot,doc_id);

	return (search==NULL) ? NULL : search->name;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?


	printf("Number of comparisons per search:%lf\n",(float)num_comp/num_search);
}

void deleteDatabaseNodes(DbNode **root){
	if((*root)==NULL){
		return;
	}

	deleteDatabaseNodes(&(*root)->left);
	deleteDatabaseNodes(&(*root)->right);
	
	free((*root));
}

void
bstdb_quit ( void ) {
	free(bookIdRecs);
	deleteDatabaseNodes(&dbRoot);
}
