//queue headerfile
#include "elementHeader.h"


typedef struct QueueNode				// 큐
{
	struct element data;							// 데이터를 입력할 구조체
	struct QueueNode *link;				// 자기자신과 같은 형식을 가르키는 포인터
}QueueNode;


void enQueue(QueueNode **, QueueNode **, element);		// 삽입
void printQueue(QueueNode *);						// 프린트
element deQueue(QueueNode **, QueueNode **);							// 인출
element deQueueHRRN(QueueNode **, QueueNode **);							// 인출
int emptyQueue(QueueNode **);						// 큐체크
void initQueue(QueueNode **, QueueNode **);			// 초기화
void addWt(QueueNode **);