#include <stdio.h>
#include <windows.h>					// system("cls")�Լ� ����� ���� �������
#include "queue.h"

void enQueue(QueueNode **front, QueueNode **rear, element item)
{
	QueueNode *tempnode;

	tempnode = (QueueNode *)malloc(sizeof(QueueNode));
	// time 14�� ��ť�ϴµ� �̻��ϰ� pid = 7�� bt 2�� �̻��ϰ� �޴´�.
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

	QueueNode *p = front;						// ����Ʈ�� *p�� �����Ѵ�.
	if (p == NULL)								// p�� NULL�� ����
	{
		printf(" end\n");						// end�� ����.
	}
	else										// p�� NULL�� �ƴ� ����
	{
		printf(" (pid : %d bt : )->", p->data.pid, p->data.bt);				// p�� data ���� ����ϰ�
		printQueue(p->link);						// �Լ��� �ٽ� �����Ѵ� (p->link�� �μ��� �ְ�, �� NULL�� ���ö����� �ݺ�)
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
		//ť�� ��� ���� �ʰ�, front�� ���� �ƴ϶�� 
		while (temp != NULL) {										//���� ť�� ������� ���� �� ���� �ݺ�
			temp->data.wt += 1;								// wt++;
															//printf("pid : %d  wt = %d\n", temp->data.pid, temp->data.wt);
			temp = temp->link;									//���� ť��
		}
	}
	else return;
	return;
}
