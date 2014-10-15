#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"
#include "bitmap.h"
#include "hash.h"
#include "limits.h"
#include "round.h"

#define TRUE	1
#define FALSE	0
#define CONTINUE -1

#define MAX_LEN	1000

#define LIST_TYPE 10
#define HASH_TYPE 11
#define BITMAP_TYPE 12

typedef unsigned long elem_type;
struct bitmap{
	size_t bit_cnt;
	elem_type *bits;
};

union component {
	
	struct list compList;
	struct bitmap* compBitmap;
	struct hash compHash;
};

struct hash_node {
	
	struct hash_elem elem;
	int data;
};

struct list_node {

	struct list_elem elem;
	int data;
};

typedef struct QueueNodeType {

	char typeFlag;
	char* tokenizedData;
	union component comp;
	struct QueueNodeType* pLink;

} QueueNode;

typedef struct LinkedQueueType {

	int currentElementCount;
	QueueNode* pFrontNode;
	QueueNode* pRearNode;

} LinkedQueue;

char* makeString(char* statement, int startPoint, int finishPoint);
void getCommandToTokenize(char* statement, LinkedQueue* pReturn);
int processCommand(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure);
int processCommandWithCreate(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure);
int processCommandWithDump(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure);
int processCommandWithDelete(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure);
int processCommandWithList(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure, int functionCode);
int processCommandWithHash(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure, int functionCode);
int processCommandWithBitmap(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure, int functionCode);

unsigned hashFunction(const struct hash_elem *e, void *aux);
void hashActionFunc(struct hash_elem *e, void *aux);
bool compareHash(struct hash_elem *a, struct hash_elem *b, void *aux);
bool compareList(struct list_elem *a, struct list_elem *b, void *aux);

/* New Data Structure Function */
void list_swap(struct list_elem *a, struct list_elem *b);
void list_shuffle(struct list *list);
unsigned hash_int_2(int i);
struct bitmap* bitmap_expand(struct bitmap *b, int size);


LinkedQueue* createLinkedQueue(void){

	LinkedQueue *pReturn = NULL;
	pReturn = (LinkedQueue*)malloc(sizeof(LinkedQueue));
	pReturn->pFrontNode = NULL;
	pReturn->pRearNode = NULL;
	pReturn->currentElementCount = 0;
	return pReturn;
}

int enqueueLQ(LinkedQueue* pQueue, char* tokenizedData){

	int ret = FALSE;
	QueueNode *pNode = NULL;
	if(pQueue != NULL){
		pNode = (QueueNode*)malloc(sizeof(QueueNode));
		if(pNode != NULL){
			pNode->tokenizedData = tokenizedData;
			pNode->pLink = NULL;
			if(pQueue->currentElementCount == 0){
				pQueue->pFrontNode = pNode;
				pQueue->pRearNode = pNode;
			}
			else {
				pQueue->pRearNode->pLink = pNode;
				pQueue->pRearNode = pNode;
			}
			pQueue->currentElementCount++;
			ret = TRUE;
		}
	}
	return ret;
}

QueueNode* dequeueLQ(LinkedQueue* pQueue){

	QueueNode* pReturn = NULL;
	if(pQueue != NULL){
		if(pQueue->currentElementCount > 0){
			pReturn = pQueue->pFrontNode;
			pQueue->pFrontNode = pQueue->pFrontNode->pLink;
			pReturn->pLink = NULL;
			pQueue->currentElementCount--;
			if(pQueue->currentElementCount == 0){
				pQueue->pRearNode = NULL;
			}
		}
	}
	return pReturn;
}

void deleteLinkedQueue(LinkedQueue* pQueue){

	QueueNode *pNode = NULL;
	QueueNode *pDelNode = NULL;

	if(pQueue != NULL){
		pNode = pQueue->pFrontNode;
		while(pNode != NULL){
			pDelNode = pNode;
			pNode = pNode->pLink;
			free(pDelNode);
		}
		free(pQueue);
	}
}



