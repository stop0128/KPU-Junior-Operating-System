#include <stdio.h>
#include <malloc.h>
#include "BinarySearchTree.h"

// 순환 탐색 함수
/*
TreeNode *search(TreeNode *node, int key)
{
if (node == NULL) return NULL;
if (key == node->data) return node;
else if (key < node->data)
return search(node->left, key);
else
return search(node->right, key);
}
*/

TreeNode *treeSearch(TreeNode *node, element key)
{
	while (node != NULL) {
		if (key.bt == node->data.bt) return node;
		else if (key.bt < node->data.bt)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

TreeNode *treeSearchMinimum(TreeNode *node)
{
	if (node == NULL) return NULL;
	else if (node->left == NULL) return node;
	treeSearchMinimum(node->left);
}

void treeInsert_node(TreeNode **root, element key)
{
	TreeNode *p, *t;						// p 부모노드, t 현재노드
	TreeNode *n;

	t = *root;
	p = NULL;

	// 탐색 bt기준
	while (t != NULL) {
		if (key.bt == t->data.bt) return;
		p = t;
		if (key.bt < p->data.bt) t = p->left;
		else t = p->right;
	}
	// key가 트리안에 없으므로 삽입
	// 트리 노드 구성
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	// 데이터 복사
	n->data = key;
	n->left = n->right = NULL;
	// 부모노드와 연결
	if (p != NULL)
		if (key.bt < p->data.bt)
			p->left = n;
		else p->right = n;
	else *root = n;
}

void treeDelete_node(TreeNode **root, element key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key를 갖는 노드 t를 탐색, p는 부모 노드

	p = NULL;
	t = *root;

	// key를 갖는 노드 t를 탐색
	while (t != NULL && t->data.bt != key.bt)
	{
		p = t;
		t = (key.bt < p->data.bt) ? p->left : p->right;
	}
	// 탐색이 종료된 시점
	if (t == NULL)
	{
		printf("key is not in the three");
		return;
	}
	// 첫번째 경우 : 단말 노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else
			*root = NULL;
	}
	// 두번째 경우 : 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)
				p->left = child;
			else p->right = child;
		}
		else
			*root = child;
	}

	// 세번째 경우 : 두 개의 자식을 가지는 경우
	else {
		succ_p = t;
		succ = t->right;
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		t->data = succ->data;
		t = succ;
	}
	free(t);
}

