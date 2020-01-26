/*
 ============================================================================
 Name        : PreAssign_Feb20_Q_8.c
 Author      : Shivam Palaskar
 Version     :
 Copyright   : Open source
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Moive {
	char movId[3]; // Though Movie ID is of 1 character we need to store NULL(\0) character at the end
	char movTitle[40];
	char movGenres[50];
	struct Movie* nextNode;
} MOVIE;

MOVIE *head = NULL;
MOVIE* createNode();
void addNodeLast(char[]);
MOVIE* getLastNode();
void displayNodes();
void findMovieByName(char[]);
void findMovieByGen(char[]);

int main(void) {
	setvbuf(stdout,NULL,_IONBF,0);
	FILE *fp;
	char s[200];
	fp = fopen("G:\\CDAC\\Git_Repository\\PreAssign_Feb20_Q_8\\PreAssign_Feb20_Q_8\\file.csv", "r");
	if (fp == NULL) {
		printf("Cannot Open File");
		return 0;
	}
	while(fgets(s, 199, fp)!=NULL){
		addNodeLast(s);
	}
	fclose(fp);
	displayNodes();

	int choice;
	char movName[40],genName[10];
	do {
		printf("\n1) Find Movies By Name");
		printf("\n2) Find Movies By Genres");
		printf("\n3) Exit");
		printf("\n Enter Choice : ");
		fflush(stdin);
		scanf("%d", &choice);
		switch(choice){
		case 1:
			printf("\nEnter Name of movie : ");
			fflush(stdin);
			scanf("%[^\n]s",movName);
			findMovieByName(movName);
			break;
		case 2:
			printf("\nEnter Genres Name : ");
			fflush(stdin);
			scanf("%[^\n]s", genName);
			findMovieByGen(genName);
			break;
		}
	} while (choice!=3);
	return EXIT_SUCCESS;
}

void findMovieByGen(char genName[]){
	MOVIE* tempPtr;
	tempPtr = head;
	char genre[50];
	while (tempPtr != NULL) {
		strcpy(genre,tempPtr->movGenres);
		char *token = strtok(genre,"|");
		while(token !=NULL){
			if(!(strcasecmp(token,genName))){
				printf("%s,%s,%s\n", tempPtr->movId, tempPtr->movTitle,tempPtr->movGenres);
			}
				token = strtok(NULL,"|");
		}
		tempPtr = tempPtr->nextNode;
	}
}

void findMovieByName(char movName[40]) {
	MOVIE* tempPtr;
	tempPtr = head;
	while (tempPtr != NULL) {
		if(!(strcasecmp(tempPtr->movTitle,movName)))
				printf("%s,%s,%s\n", tempPtr->movId, tempPtr->movTitle,tempPtr->movGenres);
		tempPtr = tempPtr->nextNode;
	}
}

/*// Using strtok() Function  // It has some problem in finding by Genres funcionality

MOVIE* createNode(char s[200]){
	MOVIE* newNode = (MOVIE*) malloc(sizeof(MOVIE));
	newNode->nextNode = NULL;
	char *token = strtok(s,",");
	int check =1;
	while (token != NULL) {
		if (check == 1)
			strcpy(newNode->movId,token);
		if (check == 2)
			strcpy(newNode->movTitle,token);
		if (check == 3)
			strcpy(newNode->movGenres,token); // As \n is already present in the string it will be automatically carry forward in to the node
		check++;
		token = strtok(NULL, ",");
	}
	return newNode;
}*/

// Without using strtok() fucntion

MOVIE* createNode(char s[200]) {
	MOVIE* newNode = (MOVIE*) malloc(sizeof(MOVIE));
	newNode->nextNode = NULL;

	int start = 0, check = 1;
	while (check <= 3) {
		int j = 0;
		char tempChar[50];
		while (s[start] != ',' && s[start] != '\n') {
			tempChar[j] = s[start];
			start++;
			j++;
		}
		tempChar[j] = '\0';
		start++;
		if (check == 1){
			strcpy(newNode->movId, tempChar);
			//printf("* %s\n",newNode->movId);
		}
		if (check == 2){
			strcpy(newNode->movTitle, tempChar);
			//printf("* %s\n",newNode->movTitle);
		}

		if (check == 3){
			strcpy(newNode->movGenres, tempChar);
			//printf("* %s\n",newNode->movGenres);
		}
		check++;
	}
	return newNode;
}

void addNodeLast(char s[200]) {
	MOVIE* newNode = createNode(s);
	if (head == NULL)
		head = newNode;
	else {
		MOVIE* lastNode = getLastNode();
		lastNode->nextNode = newNode;
	}
}

MOVIE* getLastNode() {
	MOVIE* trav = head;
	MOVIE* lastNode;
	while (trav != NULL) {
		lastNode = trav;
		trav = trav->nextNode;
	}
	return lastNode;
}

void displayNodes() {
	MOVIE* tempPtr;
	tempPtr = head;
	while (tempPtr != NULL) {
		printf("%s,%s,%s\n", tempPtr->movId, tempPtr->movTitle,tempPtr->movGenres);
		tempPtr = tempPtr->nextNode;
	}
}

/*printf("\nfp->base : %u",fp->_base);
 printf("\nfp->_bufsiz : %d",fp->_bufsiz);
 printf("\nfp->_charbuf : %d",fp->_charbuf);
 printf("\nfp->_cnt : %d",fp->_cnt);
 printf("\nfp->_file : %d",fp->_file);
 printf("\nfp->_flag : %d",fp->_flag);
 printf("\nfp->_ptr : %u",fp->_ptr);
 printf("\nfp->_tmpfname : %u",fp->_tmpfname);
 printf("\n*fp : %d",*fp); // output : 0
 printf("\nfp : %d",fp);
 printf("\n&fp->_ptr : %u\n",&fp->_ptr);*/

/*while(1){
 ch = fgetc(fp);
 if(ch==EOF)
 break;
 printf("%c",ch);
 }*/

