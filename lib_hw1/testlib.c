#include "testlib.h"

int main(int argc, char* argv[]){

	int i=0, count=0, exitFlag=FALSE;
	char cmd_buffer[MAX_LEN];
	LinkedQueue* tokenizedCommand = NULL;
	LinkedQueue* savedDataStructure = NULL;

	tokenizedCommand = createLinkedQueue();
	savedDataStructure = createLinkedQueue();

	while(1){

		fgets(cmd_buffer, sizeof(cmd_buffer), stdin);
		cmd_buffer[strlen(cmd_buffer)-1] = '\0';

		getCommandToTokenize(cmd_buffer, tokenizedCommand);
		exitFlag = processCommand(tokenizedCommand, savedDataStructure);
		if(exitFlag == TRUE){
			deleteLinkedQueue(tokenizedCommand);
			deleteLinkedQueue(savedDataStructure);
			return TRUE;
		}

		count = tokenizedCommand->currentElementCount;
		for(i=0; i<count; i++){
			free(dequeueLQ(tokenizedCommand));
		}
		
	}

	return TRUE;
}

void getCommandToTokenize(char* statement, LinkedQueue* pReturn){

	int i=0, startPoint=0, length=strlen(statement);
	char* tokenizedCommand = NULL;

	for(i=0; i<=length; i++){

		// Initiallize tokenizedData for 'makeString' function.
		tokenizedCommand = NULL;
		switch(statement[i]){

		// Case 'space', 'tap', or end of statement
		case 32: case 9: case '\0':
			tokenizedCommand = makeString(statement, startPoint, i-1);
			
			if(strlen(tokenizedCommand) != 0){
				enqueueLQ(pReturn, tokenizedCommand);
			}
			startPoint = i+1;
			break;

		}
	}
	return;
}

int processCommand(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure){

	int count=tokenizedCommand->currentElementCount;
	QueueNode* pNode = tokenizedCommand->pFrontNode;

	/* general function  */
	if(count == 1 && strcmp(pNode->tokenizedData, "quit") == 0){
		return TRUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "create") == 0){
		processCommandWithCreate(tokenizedCommand, savedDataStructure);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "dumpdata") == 0){
		processCommandWithDump(tokenizedCommand, savedDataStructure);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "delete") == 0){
		processCommandWithDelete(tokenizedCommand, savedDataStructure);
		return CONTINUE;
	}

	/* bitmap function */
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_mark") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 0);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_all") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 1);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_any") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 2);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_contains") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 3);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_count") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 4);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_dump") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 5);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_expand") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 6);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_set_all") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 7);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_flip") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 8);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_none") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 9);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_reset") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 10);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_scan") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 11);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_scan_and_flip") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 12);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_set") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 13);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_set_multiple") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 14);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_size") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 15);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "bitmap_test") == 0){
		processCommandWithBitmap(tokenizedCommand, savedDataStructure, 16);
		return CONTINUE;
	}

	/* hash function */
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_insert") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 0);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_apply") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 1);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_delete") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 2);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_empty") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 3);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_size") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 4);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_clear") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 5);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_find") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 6);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "hash_replace") == 0){
		processCommandWithHash(tokenizedCommand, savedDataStructure, 7);
		return CONTINUE;
	}
	

	/* list function */
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_insert") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 0);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_remove") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 1);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_push_front") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 2);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_push_back") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 3);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_pop_front") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 4);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_pop_back") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 5);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_sort") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 6);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_reverse") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 7);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_splice") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 8);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_swap") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 9);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_shuffle") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 10);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_unique") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 11);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_front") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 12);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_back") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 13);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_insert_ordered") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 14);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_max") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 15);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_min") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 16);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_empty") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 17);
		return CONTINUE;
	}
	else if(count > 0 && strcmp(pNode->tokenizedData, "list_size") == 0){
		processCommandWithList(tokenizedCommand, savedDataStructure, 18);
		return CONTINUE;
	}
	else {
		return FALSE;
	}

}

int processCommandWithCreate(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure){

	int count=tokenizedCommand->currentElementCount;	
	QueueNode* pNode = tokenizedCommand->pFrontNode;
	hash_less_func* hashLess = &compareHash;
	hash_hash_func* hashHash = &hashFunction;

	if(count == 3 && strcmp(pNode->pLink->tokenizedData, "list") == 0){
		enqueueLQ(savedDataStructure, makeString(pNode->pLink->pLink->tokenizedData, 0, strlen(pNode->pLink->pLink->tokenizedData)));
		savedDataStructure->pRearNode->typeFlag = LIST_TYPE;
		list_init(&(savedDataStructure->pRearNode->comp.compList));	
	}
	else if(count == 3 && strcmp(pNode->pLink->tokenizedData, "hashtable") == 0){
		enqueueLQ(savedDataStructure, makeString(pNode->pLink->pLink->tokenizedData, 0, strlen(pNode->pLink->pLink->tokenizedData)));
		savedDataStructure->pRearNode->typeFlag = HASH_TYPE;
		hash_init(&(savedDataStructure->pRearNode->comp.compHash), hashHash, hashLess, NULL);
	}

	else if(count == 4 && strcmp(pNode->pLink->tokenizedData, "bitmap") == 0){
		enqueueLQ(savedDataStructure, makeString(pNode->pLink->pLink->tokenizedData, 0, strlen(pNode->pLink->pLink->tokenizedData)));
		savedDataStructure->pRearNode->typeFlag = BITMAP_TYPE;
		savedDataStructure->pRearNode->comp.compBitmap = bitmap_create(atoi(pNode->pLink->pLink->pLink->tokenizedData));
	}

	
}

int processCommandWithDump(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure){
	
	int i=0, type=0, count=tokenizedCommand->currentElementCount;
	char* dataName = NULL;
	QueueNode* pNode = tokenizedCommand->pFrontNode;
	QueueNode* pSearch = savedDataStructure->pFrontNode;
	struct list_elem *elemSearch = NULL;
	struct list_node *nodeSearch = NULL;
	struct hash_iterator hashSearch;
	struct hash_node *elemHashSearch = NULL;

	for(i=0; i<savedDataStructure->currentElementCount; i++){
		if(strcmp(pSearch->tokenizedData, pNode->pLink->tokenizedData) == 0){
			dataName = pSearch->tokenizedData;
			type = pSearch->typeFlag;
			break;
		}
		pSearch = pSearch->pLink;
	}

	switch(type){

	case BITMAP_TYPE:
		
		for(i=0; i<bitmap_size(pSearch->comp.compBitmap); i++){
			if(bitmap_test(pSearch->comp.compBitmap, i) == true){
				printf("1");
			}
			else {
				printf("0");
			}
		}
		printf("\n");
		break;

	case LIST_TYPE:
	
		if(list_empty(&(pSearch->comp.compList)) == true){
			return CONTINUE;
		}

		elemSearch = list_begin(&(pSearch->comp.compList));
		while(TRUE){

			nodeSearch = list_entry(elemSearch, struct list_node, elem);
			printf("%d", nodeSearch->data);
			elemSearch = list_next(elemSearch);
			if(elemSearch == list_end(&(pSearch->comp.compList))){
				printf("\n");
				break;
			}
			printf(" ");
		}
		

		break;

	case HASH_TYPE:

		if(hash_empty(&(pSearch->comp.compHash)) == true){
			return CONTINUE;
		}

		hash_first(&hashSearch, &pSearch->comp.compHash);
		while(hash_next(&hashSearch)){
			elemHashSearch = hash_entry(hash_cur(&hashSearch), struct hash_node, elem);
			printf("%d ", elemHashSearch->data);
		}
		printf("\n");
		break;

	}
	
}

int processCommandWithDelete(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure){

	int i=0, size=0, type=0, count=tokenizedCommand->currentElementCount;
	char* dataName = NULL;
	QueueNode* pNode = tokenizedCommand->pFrontNode;
	QueueNode* pSearch = savedDataStructure->pFrontNode;
	QueueNode* pRemove = NULL;
	struct list_elem *elemSearch = NULL;

	for(i=0; i<savedDataStructure->currentElementCount; i++){
		if(strcmp(pSearch->tokenizedData, pNode->pLink->tokenizedData) == 0){
			dataName = pSearch->tokenizedData;
			type = pSearch->typeFlag;
			break;
		}
		pSearch = pSearch->pLink;
	}

	switch(type){

	case BITMAP_TYPE:

		bitmap_destroy(pSearch->comp.compBitmap);
		size = savedDataStructure->currentElementCount;
		pSearch = savedDataStructure->pFrontNode;

		for(i=0; i<size; i++){
			if(strcmp(pSearch->tokenizedData, dataName) == 0){
				free(dequeueLQ(savedDataStructure));
				break;
			}

			pSearch = pSearch->pLink;
			savedDataStructure->pRearNode->pLink = savedDataStructure->pFrontNode;
			savedDataStructure->pRearNode = savedDataStructure->pRearNode->pLink;
			savedDataStructure->pFrontNode = savedDataStructure->pRearNode->pLink;
			savedDataStructure->pRearNode->pLink = NULL;
		}

		break;
	
	case LIST_TYPE:
		
		size = list_size(&(pSearch->comp.compList));
		
		for(i=0; i<size; i++){
			elemSearch = list_pop_front(&(pSearch->comp.compList));
			free(list_entry(elemSearch, struct list_node, elem));
		}
		
		size = savedDataStructure->currentElementCount;
		pSearch = savedDataStructure->pFrontNode;

		for(i=0; i<size; i++){
	
			if(strcmp(pSearch->tokenizedData, dataName) == 0){
				free(dequeueLQ(savedDataStructure));
				break;
			}

			pSearch = pSearch->pLink;
			savedDataStructure->pRearNode->pLink = savedDataStructure->pFrontNode;
			savedDataStructure->pRearNode = savedDataStructure->pRearNode->pLink;
			savedDataStructure->pFrontNode = savedDataStructure->pRearNode->pLink;
			savedDataStructure->pRearNode->pLink = NULL;

		}

		break;

	case HASH_TYPE:

		break;
	}
}

int processCommandWithBitmap(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure, int functionCode){

	int i=0, operand_1=0, operand_2=0;
	char *bitmapName = NULL, *strBool = NULL;
	QueueNode *pNode = tokenizedCommand->pFrontNode;
	QueueNode *pSearch = savedDataStructure->pFrontNode;
	struct bitmap *elemSearch = NULL;
	bool ret=false;

	// Step 1. Find the bitmap name with operand.
	for(i=0; i<savedDataStructure->currentElementCount; i++){
		if(strcmp(pSearch->tokenizedData, pNode->pLink->tokenizedData) == 0){
			bitmapName = pSearch->tokenizedData;
			break;
		}
		pSearch = pSearch->pLink;
	}
	elemSearch = pSearch->comp.compBitmap;

	// Step 2. Operate with switch function.
	switch(functionCode){

	// Case 0. bitmap_mark
	case 0:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		bitmap_mark(elemSearch, operand_1);
		break;

	// Case 1. bitmap_all
	case 1:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		ret = bitmap_all(elemSearch, operand_1, operand_2);
		if(ret == true){
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		break;

	// Case 2. bitmap_any
	case 2:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		ret = bitmap_any(elemSearch, operand_1, operand_2);
		if(ret == true){
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		break;

	// Case 3. bitmap_contains
	case 3:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		strBool = pNode->pLink->pLink->pLink->pLink->tokenizedData;

		if(strcmp(strBool, "true") == 0){
			ret = bitmap_contains(elemSearch, operand_1, operand_2, true);
		}
		else {
			ret = bitmap_contains(elemSearch, operand_1, operand_2, false);
		}
		if(ret == true){
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		break;

	// Case 4. bitmap_count
	case 4:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		strBool = pNode->pLink->pLink->pLink->pLink->tokenizedData;

		if(strcmp(strBool, "true") == 0){
			printf("%d\n", bitmap_count(elemSearch, operand_1, operand_2, true));
		}
		else {
			printf("%d\n", bitmap_count(elemSearch, operand_1, operand_2, false));
		}

		break;

	// Case 5. bitmap_dump
	case 5:
		bitmap_dump(elemSearch);
		break;

	// Case 6. bitmap_expand
	case 6:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		elemSearch = bitmap_expand(elemSearch, operand_1);
		break;

	// Case 7. bitmap_set_all
	case 7:
		strBool = pNode->pLink->pLink->tokenizedData;
		if(strcmp(strBool, "true") == 0){
			bitmap_set_all(elemSearch, true);
		}
		else {
			bitmap_set_all(elemSearch, false);
		}
		break;

	// Case 8. bitmap_flip
	case 8:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		bitmap_flip(elemSearch, operand_1);
		break;

	// Case 9. bitmap_none
	case 9:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		ret = bitmap_none(elemSearch, operand_1, operand_2);
		if(ret == true){
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		break;

	// Case 10. bitmap_reset
	case 10:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		bitmap_reset(elemSearch, operand_1);
		break;

	// Case 11. bitmap_scan
	case 11:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		strBool = pNode->pLink->pLink->pLink->pLink->tokenizedData;
		if(strcmp(strBool, "true") == 0){
			ret = true;
		}
		else {
			ret = false;
		}
		printf("%u\n", (size_t)bitmap_scan(elemSearch, operand_1, operand_2, ret));
		break;

	// Case 12. bitmap_scan_and_flip
	case 12:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		strBool = pNode->pLink->pLink->pLink->pLink->tokenizedData;
		if(strcmp(strBool, "true") == 0){
			ret = true;
		}
		else {
			ret = false;
		}
		printf("%u\n", (size_t)bitmap_scan_and_flip(elemSearch, operand_1, operand_2, ret));
		break;

	// Case 13. bitmap_set
	case 13:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		strBool = pNode->pLink->pLink->pLink->tokenizedData;
		if(strcmp(strBool, "true") == 0){
			ret = true;
		}
		else {
			ret = false;
		}
		bitmap_set(elemSearch, operand_1, ret);
		break;

	// Case 14. bitmap_set_multiple
	case 14:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
		strBool = pNode->pLink->pLink->pLink->pLink->tokenizedData;
		if(strcmp(strBool, "true") == 0){
			ret = true;
		}
		else {
			ret = false;
		}
		bitmap_set_multiple(elemSearch, operand_1, operand_2, ret);
		break;

	// Case 15. bitmap_size
	case 15:
		printf("%d\n", bitmap_size(elemSearch));
		break;

	// Case 16. bitmap_test
	case 16:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		ret = bitmap_test(elemSearch, operand_1);
		if(ret == true){
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		break;

	}

}

int processCommandWithHash(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure, int functionCode){

	int i=0, operand_1=0, operand_2=0;
	char *hashName = NULL, *strParam = NULL;
	bool ret = false;
	QueueNode* pNode = tokenizedCommand->pFrontNode;
	QueueNode* pSearch = savedDataStructure->pFrontNode;
	struct hash_elem *elemSearch = NULL;
	struct hash_node *pNew = NULL, *hashSearch = NULL;
	struct hash_iterator hashIterator;
	
	hash_action_func *hashAction = &hashActionFunc;
	hash_less_func *hashLess = &compareHash;
	hash_hash_func *hashHash = &hashFunction;

	// Step 1. Find the hash name with operand.
	for(i=0; i<savedDataStructure->currentElementCount; i++){
		if(strcmp(pSearch->tokenizedData, pNode->pLink->tokenizedData) == 0){
			hashName = pSearch->tokenizedData;
			break;
		}
		pSearch = pSearch->pLink;
	}
	elemSearch = &pSearch->comp.compHash;

	// Step 2. Operate with switch function.
	switch(functionCode){

	// Case 0. hash_insert
	case 0:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
			
		pNew = (struct hash_node*)malloc(sizeof(struct hash_node));
		pNew->data = operand_1;
		hash_insert(&(pSearch->comp.compHash), &(pNew->elem));
		break;
	
	// Case 1. hash_apply
	case 1:
		strParam = pNode->pLink->pLink->tokenizedData;
		if(strcmp(strParam, "square") == 0){
			hash_first(&hashIterator, &pSearch->comp.compHash);
			while(hash_next(&hashIterator)){
				hashSearch = hash_entry(hash_cur(&hashIterator), struct hash_node, elem);
				hashSearch->data = hashSearch->data * hashSearch->data;
			}
		}
		else if(strcmp(strParam, "triple") == 0){
			hash_first(&hashIterator, &pSearch->comp.compHash);
			while(hash_next(&hashIterator)){
				hashSearch = hash_entry(hash_cur(&hashIterator), struct hash_node, elem);
				hashSearch->data = hashSearch->data * hashSearch->data * hashSearch->data;
			}
		}
		break;

	// Case 2. hash_delete
	case 2:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		hash_first(&hashIterator, &pSearch->comp.compHash);
		while(hash_next(&hashIterator)){
			hashSearch = hash_entry(hash_cur(&hashIterator), struct hash_node, elem);
			if(hashSearch->data == operand_1){
				hash_delete(&pSearch->comp.compHash, hash_cur(&hashIterator));
				break;
			}
		}

		break;
	
	// Case 3. hash_empty
	case 3:
		ret = hash_empty(&pSearch->comp.compHash);
		if(ret == true){
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		break;

	// Case 4. hash_size
	case 4:
		printf("%d\n", hash_size(&pSearch->comp.compHash));
		break;

	// Case 5. hash_clear
	case 5:
		hash_clear(&pSearch->comp.compHash, hashAction);		
		break;
	
	// Case 6. hash_find
	case 6:
		ret = false;
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		hash_first(&hashIterator, &pSearch->comp.compHash);
		while(hash_next(&hashIterator)){
			hashSearch = hash_entry(hash_cur(&hashIterator), struct hash_node, elem);
			if(hashSearch->data == operand_1){
				ret = true;
				break;
			}
		}
		elemSearch = hash_find(&pSearch->comp.compHash, &hashSearch->elem);
		if(ret == true){
			printf("%d\n", hashSearch->data);
		}
		break;
	
	// Case 7. hash_replace
	case 7:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		hash_first(&hashIterator, &pSearch->comp.compHash);
		ret = false;

		pNew = (struct hash_node*)malloc(sizeof(struct hash_node));
		pNew->data = operand_1;
		
		while(hash_next(&hashIterator)){
			hashSearch = hash_entry(hash_cur(&hashIterator), struct hash_node, elem);
			if(hashSearch->data == operand_1){
				free(hash_replace(&pSearch->comp.compHash, &pNew->elem));
				ret = true;
				break;
			}
		}

		if(ret == false){
			hash_replace(&pSearch->comp.compHash, &pNew->elem);
		}

		break;
	
	}

	return FALSE;
}

int processCommandWithList(LinkedQueue* tokenizedCommand, LinkedQueue* savedDataStructure, int functionCode){


	int i=0, operand_1=0, operand_2=0, operand_3=0;
	char *listName = NULL, *paramListName = NULL;
	QueueNode* pNode = tokenizedCommand->pFrontNode;
	QueueNode* pSearch = savedDataStructure->pFrontNode;
	QueueNode* pParamSearch = savedDataStructure->pFrontNode;
	struct list_elem *elemSearch = NULL, *paramElemSearch = NULL, *paramElemSearch_1 = NULL, *paramElemSearch_2 = NULL;
	struct list_node *pNew = NULL;
	struct list_node *nodeSearch = NULL;
	list_less_func *listLess = &compareList;

	// Step 1. Find the list name with operand.
	for(i=0; i<savedDataStructure->currentElementCount; i++){
		if(strcmp(pSearch->tokenizedData, pNode->pLink->tokenizedData) == 0){
			listName = pSearch->tokenizedData;
			break;
		}
		pSearch = pSearch->pLink;
	}
	elemSearch = list_begin(&pSearch->comp.compList);


	// Step 2. Operate with switch function.
	switch(functionCode){
	
	// Case 0. list_insert
	case 0:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);
	
		pNew = (struct list_node*)malloc(sizeof(struct list_node));
		pNew->data = operand_2;

		for(i=0; i<operand_1; i++){
			if(elemSearch == list_end(&(pSearch->comp.compList))){
				break;
			}
			elemSearch = list_next(elemSearch);
		}
		list_insert(elemSearch, &(pNew->elem));
		break;
	
	// Case 1. list_remove
	case 1:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		for(i=0; i<operand_1; i++){
			if(elemSearch == list_end(&(pSearch->comp.compList))){
				break;
			}
			elemSearch = list_next(elemSearch);
		}
		elemSearch = list_remove(elemSearch);
		//free(list_entry(elemSearch, struct list_node, elem));
		break;

	// Case 2. list_push_front
	case 2:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);

		pNew = (struct list_node*)malloc(sizeof(struct list_node));
		pNew->data = operand_1;
		list_push_front(&(pSearch->comp.compList), &(pNew->elem));
		break;

	// Case 3. list_push_back
	case 3:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);

		pNew = (struct list_node*)malloc(sizeof(struct list_node));
		pNew->data = operand_1;
		list_push_back(&(pSearch->comp.compList), &(pNew->elem));
		break;

	// Case 4. list_pop_front
	case 4:
		elemSearch = list_pop_front(&(pSearch->comp.compList));
		free(list_entry(elemSearch, struct list_node, elem));
		break;

	// Case 5. list_pop_back
	case 5:
		elemSearch = list_pop_back(&(pSearch->comp.compList));
		free(list_entry(elemSearch, struct list_node, elem));
		break;

	// Case 6. list_sort
	case 6:
		list_sort(&(pSearch->comp.compList), listLess, NULL);	
		break;

	// Case 7. list_reverse
	case 7:
		list_reverse(&(pSearch->comp.compList));
		break;

	// Case 8. list_splice
	case 8:
		for(i=0; i<savedDataStructure->currentElementCount; i++){
			if(strcmp(pParamSearch->tokenizedData, pNode->pLink->pLink->pLink->tokenizedData) == 0){
				paramListName = pParamSearch->tokenizedData;
				break;
			}
			pParamSearch = pParamSearch->pLink;
		}
		paramElemSearch = list_begin(&pParamSearch->comp.compList);
		
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->pLink->tokenizedData);
		operand_3 = atoi(pNode->pLink->pLink->pLink->pLink->pLink->tokenizedData);

		paramElemSearch_1 = paramElemSearch;
		paramElemSearch_2 = paramElemSearch;

		for(i=0; i<operand_1; i++){
			if(elemSearch == list_end(&(pSearch->comp.compList))){
				break;
			}
			elemSearch = list_next(elemSearch);
		}
		
		for(i=0; i<operand_2; i++){
			if(paramElemSearch_1 == list_end(&(pParamSearch->comp.compList))){
				break;
			}
			paramElemSearch_1 = list_next(paramElemSearch_1);
		}

		for(i=0; i<operand_3; i++){
			if(paramElemSearch_2 == list_end(&(pParamSearch->comp.compList))){
				break;
			}
			paramElemSearch_2 = list_next(paramElemSearch_2);
		}

		list_splice(elemSearch, paramElemSearch_1, paramElemSearch_2);
		break;

	// Case 9. list_swap
	case 9:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		operand_2 = atoi(pNode->pLink->pLink->pLink->tokenizedData);

		paramElemSearch_1 = elemSearch;
		paramElemSearch_2 = elemSearch;

		for(i=0; i<operand_1; i++){
			if(paramElemSearch_1 == list_end(&(pSearch->comp.compList))){
				break;
			}
			paramElemSearch_1 = list_next(paramElemSearch_1);
		}

		for(i=0; i<operand_2; i++){
			if(paramElemSearch_2 == list_end(&(pSearch->comp.compList))){
				break;
			}
			paramElemSearch_2 = list_next(paramElemSearch_2);
		}

		list_swap(paramElemSearch_1, paramElemSearch_2);

		break;
	
	// Case 10. list_shuffle
	case 10:
		list_shuffle(&(pSearch->comp.compList));
		break;

	// Case 11. list_unique
	case 11:
		
		if(pNode->pLink->pLink != NULL){
			for(i=0; i<savedDataStructure->currentElementCount; i++){
				if(strcmp(pParamSearch->tokenizedData, pNode->pLink->pLink->tokenizedData) == 0){
					paramListName = pParamSearch->tokenizedData;
					break;
				}
				pParamSearch = pParamSearch->pLink;
				list_unique(&(pSearch->comp.compList), &(pParamSearch->comp.compList), listLess, NULL);
			}
		}
		else {
			list_unique(&(pSearch->comp.compList), NULL, listLess, NULL);
		}

		break;

	// Case 12. list_front
	case 12:
		elemSearch = list_front(&(pSearch->comp.compList));
		nodeSearch = list_entry(elemSearch, struct list_node, elem);
		printf("%d\n", nodeSearch->data);
		break;

	// Case 13. list_back
	case 13:
		elemSearch = list_back(&(pSearch->comp.compList));
		nodeSearch = list_entry(elemSearch, struct list_node, elem);
		printf("%d\n", nodeSearch->data);
		break;

	// Case 14. list_insert_ordered
	case 14:
		operand_1 = atoi(pNode->pLink->pLink->tokenizedData);
		pNew = (struct list_node*)malloc(sizeof(struct list_node));
		pNew->data = operand_1;
		list_insert_ordered(&(pSearch->comp.compList), &(pNew->elem), listLess, NULL);
		break;
	
	// Case 15. list_max
	case 15:
		elemSearch = list_max(&(pSearch->comp.compList), listLess, NULL);
		nodeSearch = list_entry(elemSearch, struct list_node, elem);
		printf("%d\n", nodeSearch->data);
		break;

	// Case 16. list_min
	case 16:
		elemSearch = list_min(&(pSearch->comp.compList), listLess, NULL);
		nodeSearch = list_entry(elemSearch, struct list_node, elem);
		printf("%d\n", nodeSearch->data);
		break;

	// Case 17. list_empty
	case 17:
		if(list_empty(&(pSearch->comp.compList)) == true){
			printf("true\n");
		}
		else {
			printf("false\n");
		}
		break;

	// Case 18. list_size
	case 18:
		printf("%d\n", list_size(&(pSearch->comp.compList)));
		break;


	}

	return FALSE;

}

char* makeString(char* statement, int startPoint, int finishPoint){

	int i=0, j=0;
	char* stringValue = NULL;

	// To make string, calculate string size (add 1 for 'null' character (end of string)
	stringValue = (char*)malloc(sizeof(char)*(finishPoint - startPoint + 2));

	for(i=startPoint; i<=finishPoint; i++){
		stringValue[j++] = statement[i];
	}
	stringValue[j] = '\0';

	return stringValue;
}

unsigned hashFunction(const struct hash_elem *e, void *aux){
	
	return hash_int(hash_entry(e, struct hash_node, elem)->data);
}

void hashActionFunc(struct hash_elem *e, void *aux){
	
}

unsigned hash_int_2(int i){
	
	return (i+20)%4;
}

bool compareHash(struct hash_elem *a, struct hash_elem *b, void *aux){

	int operand_1=0, operand_2=0;

	operand_1 = hash_entry(a, struct hash_node, elem)->data;
	operand_2 = hash_entry(b, struct hash_node, elem)->data;

	if(operand_1 < operand_2){
		return true;
	}
	else {
		return false;
	}
}

bool compareList(struct list_elem *a, struct list_elem *b, void *aux){
	
	int operand_1=0, operand_2=0;

	operand_1 = list_entry(a, struct list_node, elem)->data;
	operand_2 = list_entry(b, struct list_node, elem)->data;

	if(operand_1 < operand_2){
		return true;
	}
	else {
		return false;
	}
}

void list_swap(struct list_elem *a, struct list_elem *b){

	int operand_1=0, operand_2=0;

	operand_1 = list_entry(a, struct list_node, elem)->data;
	operand_2 = list_entry(b, struct list_node, elem)->data;

	list_entry(a, struct list_node, elem)->data = operand_2;
	list_entry(b, struct list_node, elem)->data = operand_1;

}

void list_shuffle(struct list *list){

	int i=0, j=0, size=list_size(list), randomIdx=0;
	struct list_elem *operand_1=NULL, *operand_2=NULL;


	// Step 1. creating seed.
	srand(time(NULL));
	rand(); rand(); rand();
	srand(rand());

	// Step 2. randomize and swapping the data.
	for(i=0, operand_1=list_begin(list); i<size; i++, operand_1=list_next(operand_1)){
		randomIdx = rand() % size;
		for(j=0, operand_2=list_begin(list); j<randomIdx; j++){
			operand_2 = list_next(operand_2);
		}
		list_swap(operand_1, operand_2);
	}

}

struct bitmap* bitmap_expand(struct bitmap *b, int size){

	int i=0, originSize=bitmap_size(b);

	b->bit_cnt = originSize+size;
	b->bits = realloc(b->bits, (sizeof(elem_type))*(DIV_ROUND_UP((size_t)(originSize + size), sizeof(elem_type)*CHAR_BIT)));
	for(i=originSize; i<originSize+size; i++){
		bitmap_set(b, i, false);
	}

	return b;
}
