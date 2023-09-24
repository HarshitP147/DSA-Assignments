#include <stdio.h>

int main(){
	int age;
	char name[100];

	printf("Name >> ");
	scanf("%s",name);

	printf("Age >> ");
	scanf("%d",&age);

	printf("Hello %s (%d)\n",name,age);

	return 0;
}
