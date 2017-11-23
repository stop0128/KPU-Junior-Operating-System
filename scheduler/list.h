#include "elementHeader.h"
#define LinkedList_list_h

typedef struct _Node{
	Lelement data;
	struct _Node *next;
	struct _Node *prev;
} Node;


typedef struct _List{
	Node *head;
	Node *tail;
} List;

void list_init(List* list);
void list_push_back(List* list, Lelement data);
void list_push_front(List* list, Lelement data);
void list_insert(List* list, Node* rhs, Lelement data);
Node* list_find(List* list, Lelement data);
Lelement list_erase(List* list);
int list_isEmpty(List* list);
void addWtList(List *);
Node* list_make_node();
Lelement list_erasebt(List* list);
