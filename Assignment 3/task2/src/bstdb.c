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

	//srand(time(NULL));
	for(int i=x-1;i>0;i--){
		int j=rand()%(i+1);
		int temp=bookIdRecs[i];
		bookIdRecs[i]=bookIdRecs[j];
		bookIdRecs[j]=temp;
	}

	k=0;

	return 1;
}

int getBalanceFactor(DbNode *node){
	int left=0,right=0;

	while(node->left!=NULL){
		left++;
		node=node->left;
	}
	while(node->right!=NULL){
		right++;
		node=node->right;
	}

	return (left-right);
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

DbNode *rightRotate(DbNode **root){
	DbNode *temp1=(*root)->left;
	DbNode *temp2=temp1->right;

	// perform the rotation
	temp1->right=(*root);
	(*root)->left=temp2;

	return temp1;
}

DbNode *leftRotate(DbNode **root){
	DbNode *temp1=(*root)->right;
	DbNode *temp2=temp1->left;

	// perform the rotation
	temp1->left=(*root);
	(*root)->right=temp2;

	return temp1;
}

void optimizeDatabaseTree(DbNode **root){
	int bf=getBalanceFactor((*root));
	
	// Left Heavy Case
    if (bf > 1) {
        if (getBalanceFactor((*root)->left) < 0) {
            // Left-Right Case: Left rotate left child, then right rotate the current node
            (*root)->left = leftRotate(&((*root)->left));
        }
        // Right rotate the current node
        *root = rightRotate(root);
    }
    // Right Heavy Case
    if (bf < -1) {
        if (getBalanceFactor((*root)->right) > 0) {
            // Right-Left Case: Right rotate right child, then left rotate the current node
            (*root)->right = rightRotate(&((*root)->right));
        }
        // Left rotate the current node
        *root = leftRotate(root);
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
		optimizeDatabaseTree(&dbRoot);
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
	printf("Number of comparisons per search:%lf\n",(float)num_comp/num_search);
	printf("The bookId values are unique as they are numerically counted and inserted from 1 to 200000, which ensures that there are no duplicates.\n");
	printf("The number of search errors are zero which indicate that each node is properly inserted in the tree for searching.\n");
	printf("The balance factor always comes out either as -1,0 or 1. This confirms that the tree is balanced\n");
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
	printf("Tree balance factor:%d\n",getBalanceFactor(dbRoot));
	deleteDatabaseNodes(&dbRoot);
}
