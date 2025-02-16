//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
void moveOddItemsToBack(LinkedList *ll) {
ListNode *cur = ll->head;
	ListNode *even_start = NULL, *even_end = NULL;
	ListNode *odd_start = NULL, *odd_end = NULL;

	while (cur != NULL){
		ListNode *next = cur->next;
		cur->next = NULL;

		if ( cur->item % 2 != 0){ //현재 노드가 홀수인경우

			if(odd_start == NULL){ //홀수리스트가 비어있을때
				odd_start =  cur;
				odd_end = cur;
			} else { // 홀수리스트가 비어있지 않았을때
				odd_end->next = cur;
				odd_end = cur;
			}

		} else { // 현재 노드가 짝수인경우
			if (even_start == NULL){
				even_start = cur;
				even_end = cur;
			} else {
				even_end->next=cur;
				even_end = cur;
			}
		}
		cur = next;
	}
	//홀짝 합치기
	if (even_start ==NULL){
		ll->head=odd_start;
	} else {
		ll->head= even_start;
		even_end->next=odd_start;
	}
	if(odd_end != NULL){
		odd_end->next = NULL;
	}
}
	


// 	if (ll == NULL || ll->head == NULL){
// 		return;
// 	}
// 	ListNode *cur, *even, *even_start, *odd, *odd_start;

// 	cur = ll->head;
// 	even_start = even = malloc(sizeof(ListNode));
// 	odd_start = odd = malloc(sizeof(ListNode));

// 	int even_cnt = 0;
// 	int odd_cnt = 0;


// 	while(1){
// 		if(odd_cnt + even_cnt == ll->size){
// 			odd->next = NULL;
// 			even->next = odd_start->next;
// 			ll->head = even_start->next;
// 			break;
// 		}

// 		if (cur->item % 2 != 0){ //현재 노드가 홀수일떄
// 			odd->next=cur;
// 			odd=cur;
// 			odd_cnt++;


// 		} else { //현재 노드가 짝수일때
// 			even->next=cur;
// 			even = cur;
// 			even_cnt++;
// 		}
// 		cur = cur->next;



// 	}
	

// }


	
	// 홀수뒤에짝수면 바까줌
	//

		// 현재아이템이 홀수이고 다음노드의아이템이 짝수이면 뒤로 한칸민다
	/* add your code here
	먼저 홀수의 개수를 찾은다음,count번 반복하면서, 매번 하나씩 놓습니다.
	중요한것은 매번반복할때마다 temp 와 count 를 초기화하는것입니다.
	!!!홀수뒤로보내기!!

	 */



///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
