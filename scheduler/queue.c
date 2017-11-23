#include <stdio.h>
#include <windows.h>					// system("cls")함수 사용을 위한 헤더파일
#include "queue.h"

void enQueue(QueueNode **front, QueueNode **rear, element item)
{
	QueueNode *tempnode;

	tempnode = (QueueNode *)malloc(sizeof(QueueNode));
	// time 14때 인큐하는데 이상하게 pid = 7과 bt 2를 이상하게 받는다.
	tempnode->data = item;
	tempnode->link = NULL;
	if (emptyQueue(front))
	{
		*front = tempnode;
		*rear = tempnode;
	}
	else
	{
		(*rear)->link = tempnode;
		(*rear) = (*rear)->link;
	}
}

void printQueue(QueueNode *front) {

	QueueNode *p = front;						// 리스트를 *p에 저장한다.
	if (p == NULL)								// p가 NULL일 경우는
	{
		printf(" end\n");						// end를 띄운다.
	}
	else										// p가 NULL이 아닐 경우는
	{
		printf(" (pid : %d bt : )->", p->data.pid, p->data.bt);				// p의 data 값을 출력하고
		printQueue(p->link);						// 함수를 다시 실행한다 (p->link를 인수를 주고, 즉 NULL이 나올때까지 반복)
	}
}

element deQueue(QueueNode **front, QueueNode **rear) {
	QueueNode *temp;
	element item;
	int i = 0;
	if (emptyQueue(front))
	{
		(*rear) = NULL;
		item.bt = -1;
		printf("Queue is NULL");
		return item;
	}
	item = (*front)->data;
	temp = *front;
	*front = (*front)->link;
	free(temp);
	return item;
}

int emptyQueue(QueueNode **front) {
	return (*front == NULL);
}

void initQueue(QueueNode **front, QueueNode **rear) {
	*front = NULL;
	*rear = NULL;
}

void addWt(QueueNode **front) {
	QueueNode *temp;

	if (!emptyQueue(&front)) {
		temp = (*front);
		//큐가 비어 있지 않고, front가 널이 아니라면 
		while (temp != NULL) {										//다음 큐가 비어있지 않을 때 까지 반복
			temp->data.wt += 1;								// wt++;
															//printf("pid : %d  wt = %d\n", temp->data.pid, temp->data.wt);
			temp = temp->link;									//다음 큐로
		}
	}
	else return;
	return;
}
