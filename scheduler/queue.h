//queue headerfile
#include "elementHeader.h"


typedef struct QueueNode				// ť
{
	struct element data;							// �����͸� �Է��� ����ü
	struct QueueNode *link;				// �ڱ��ڽŰ� ���� ������ ����Ű�� ������
}QueueNode;


void enQueue(QueueNode **, QueueNode **, element);		// ����
void printQueue(QueueNode *);						// ����Ʈ
element deQueue(QueueNode **, QueueNode **);							// ����
element deQueueHRRN(QueueNode **, QueueNode **);							// ����
int emptyQueue(QueueNode **);						// ťüũ
void initQueue(QueueNode **, QueueNode **);			// �ʱ�ȭ
void addWt(QueueNode **);