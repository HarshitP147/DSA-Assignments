#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void tree_insert(Tree_Node **root,char data){
	Tree_Node *newNode=(Tree_Node*)(malloc(sizeof(Tree_Node)));
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;

	if((*root)==NULL){
		(*root)=newNode;
	}
	else{
		Tree_Node *temp = (*root);
		while(temp!=NULL){
			/* if(temp->data == newNode->data){
				return;  // duplicate nodes are not allowed
			} */
			if((newNode->data < temp->data) && (temp->left==NULL)){
				temp->left = newNode;
			}
			else if(newNode->data < temp->data){
				temp = temp->left;
			}
			else if((newNode->data > temp->data) && (temp->right==NULL)){
				temp->right = newNode;
			}
			else if(newNode->data > temp->data){
				temp = temp->right;
			}
		}
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
    return NULL;
}

void tree_print_sorted(Tree_Node *root){
	if(root!=NULL){
		tree_print_sorted(root->left);
		printf("%c ",root->data);
		tree_print_sorted(root->right);
	}
}

void tree_delete(Tree_Node *root){
}

