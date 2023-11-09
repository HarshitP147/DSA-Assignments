#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

typedef Tree_Node node;

Tree_Node *createNode(char data){
	Tree_Node *newNode = (Tree_Node*)(malloc(sizeof(Tree_Node)));
	if(newNode){
		newNode->data=data;
		newNode->freq=1;
		newNode->left=NULL;
		newNode->right=NULL;
	}
	return newNode;
}

void tree_insert(Tree_Node **root,char data){
	if((*root)==NULL){
		(*root)=createNode(data);
		return;
	}

	int rootASCII=(*root)->data;
	int inpASCII=data;

	if(inpASCII<rootASCII){
		tree_insert(&(*root)->left,data);
	}
	else if(inpASCII>rootASCII){
		tree_insert(&(*root)->right,data);
	}
	else{
		(*root)->freq+=1;
	}
}

Tree_Node *create_bst(char data[]){
	Tree_Node *root=(Tree_Node*)(malloc(sizeof(Tree_Node)));

	if(root==NULL) return NULL;

	int i=0;
	char c;
	while(1){
		c=data[i++];
		if(c=='\0') break;
		tree_insert(&root,c);
	}

	return root;
}

Tree_Node *tree_search(Tree_Node *root,char data){
	node *search=root;
	
	int rootASCII=search->data;
	int searchASCII=data;

	while(search!=NULL){
		rootASCII=search->data;
		if(searchASCII<rootASCII){
			search=search->left;
		}
		if(searchASCII==rootASCII){
			break;
		}
		if(searchASCII>rootASCII){
			search=search->right;
		}
	}
	
	return search;
}

void tree_print_sorted(Tree_Node *root){
	if(root!=NULL){
		tree_print_sorted(root->left);
		for(int i=0;i<root->freq;i++){
			printf("%c",root->data);
		}
		tree_print_sorted(root->right);
	}
}

void tree_delete(Tree_Node *root){
	// we delete the tree using post order traversal
	if(root!=NULL){
		tree_delete(root->left);
		tree_delete(root->right);
		free(root);
	}
}

