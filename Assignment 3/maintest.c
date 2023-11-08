#include <stdio.h>
#include <stdlib.h>

#include "bst_skeleton.c"

#define MAX_SIZE 100

typedef Tree_Node node;

// Function to print the tree in a graphical form
void prettyPrintTree(node *root,char *prefix,int isLeft) {
    if (root==NULL) {
        printf("Empty tree\n");
        return;
    }

    char newPrefix[MAX_SIZE];
    sprintf(newPrefix, "%s%s", prefix, isLeft ? "│   " : "    ");

    if (root->right!=NULL) {
        prettyPrintTree(root->right, newPrefix, 0);
    }

    printf("%s%s%c\n", prefix, isLeft ? "└── " : "┌── ", root->data);

    if (root->left != NULL) {
        prettyPrintTree(root->left, newPrefix, 1);
    }
}

void printTree(node *root){
	prettyPrintTree(root,"",1);
	printf("\n");
}

int main(){
	node *root=NULL;
	
	char *data="abc";

	root=create_bst(data);
	
	printTree(root);
	printf("\n");

	return 0;
}
