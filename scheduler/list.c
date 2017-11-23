#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void list_init(List *list)
{
	list->head = NULL;
	list->tail = NULL;
}


Node* list_make_node()
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data.bt = 0;
	node->data.pid = 0;
	node->data.wt = 0;
	node->data.R = 0;
	node->next = NULL;
	node->prev = NULL;
	return node;
}


void list_push_back(List *list, Lelement data)
{
	Node *node = list_make_node();
	node->data = data;

	if (list->tail != NULL)
	{
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}
	else
	{
		list->tail = node;
		list->head = node;
	}

}

void list_push_front(List *list, Lelement data)
{
	Node * node = list_make_node();
	node->data = data;

	if (list->head != NULL)
	{
		list->head->prev = node;
		node->next = list->head;
		list->head = node;
	}

	else
	{
		list->tail = node;
		list->head = node;
	}

}

void list_insert(List* list, Node * rhs, Lelement data)
{
	Node* lhs = rhs->prev;
	if (lhs == NULL)
	{
		list_push_front(list, data);
		return;
	}

	Node *node = list_make_node();
	node->data = data;

	lhs->next = node;
	node->prev = lhs;

	node->next = rhs;
	rhs->prev = node;
}


Lelement list_erase(List* list)
{
	Node* target = list->head;
	Lelement item;
	float bigR;
	if (!list_isEmpty(&list)) {
		target->data.R = ((float)target->data.wt + (float)target->data.bt) / (float)target->data.bt;
		bigR = target->data.R;

		target = target->next;
		while (target != NULL) {
			target->data.R = ((float)target->data.wt + (float)target->data.bt) / (float)target->data.bt;
			if (target->data.R > bigR) {
				bigR = target->data.R;
			}
			target = target->next;
			// R=(w+bt)/bt   
		}
		target = list->head;
		while (target != NULL) {
			if (target->data.R == bigR) {
				if (list->head == target) {                        //�� ���� ���
					if (list->head->next == NULL) {
						list->head = NULL;                           //�� ���� ��带 ������ �� ����Ʈ�� ���
						list->tail = NULL;
					}
					else
						list->head = target->next;
				}
				else if (list->tail == target) {                     //�� ���� ���
					list->tail->prev->next = list->tail->next;
					list->tail = list->tail->prev;

				}
				else {                                          //�߰��� ���
					target->prev->next = target->next;
					target->next->prev = target->prev;
				}
				item = target->data;
				free(target);
				return item;

			}
			target = target->next;
		}
	}
	return;

}

int list_isEmpty(List* list)
{
	return (list->head == NULL && list->tail == NULL);
}
void addWtList(List *front) {
	Node *temp;

	if (!list_isEmpty(&front)) {
		temp = front->head;
		//ť�� ��� ���� �ʰ�, front�� ���� �ƴ϶�� 
		while (temp != NULL) {                              //���� ����Ʈ�� ������� ���� �� ���� �ݺ�
			temp->data.wt += 1;                        // wt++;
			temp = temp->next;                           //���� ����Ʈ
		}
	}
	else return;
	return;
}

Lelement list_erasebt(List* list)
{
	Node* target = list->head;
	Lelement item;
	int smallbt;
	if (!list_isEmpty(&list)) {
		smallbt = target->data.bt;
		target = target->next;
		while (target != NULL) {
			if (target->data.bt < smallbt) {
				smallbt = target->data.bt;
			}
			target = target->next;
			// R=(w+bt)/bt   
		}
		target = list->head;
		while (target != NULL) {
			if (target->data.bt == smallbt) {
				if (list->head == target) {                        //�� ���� ���
					if (list->head->next == NULL) {
						list->head = NULL;                           //�� ���� ��带 ������ �� ����Ʈ�� ���
						list->tail = NULL;
					}
					else
						list->head = target->next;
				}
				else if (list->tail == target) {                     //�� ���� ���
					list->tail->prev->next = list->tail->next;
					list->tail = list->tail->prev;

				}
				else {                                          //�߰��� ���
					target->prev->next = target->next;
					target->next->prev = target->prev;
				}
				item = target->data;
				free(target);
				return item;
			}
			target = target->next;
		}
	}
	return;

}
