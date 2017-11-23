#include <stdio.h>
#include <malloc.h>
#include "BinarySearchTree.h"

// ��ȯ Ž�� �Լ�
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
	TreeNode *p, *t;						// p �θ���, t ������
	TreeNode *n;

	t = *root;
	p = NULL;

	// Ž�� bt����
	while (t != NULL) {
		if (key.bt == t->data.bt) return;
		p = t;
		if (key.bt < p->data.bt) t = p->left;
		else t = p->right;
	}
	// key�� Ʈ���ȿ� �����Ƿ� ����
	// Ʈ�� ��� ����
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	// ������ ����
	n->data = key;
	n->left = n->right = NULL;
	// �θ���� ����
	if (p != NULL)
		if (key.bt < p->data.bt)
			p->left = n;
		else p->right = n;
	else *root = n;
}

void treeDelete_node(TreeNode **root, element key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key�� ���� ��� t�� Ž��, p�� �θ� ���

	p = NULL;
	t = *root;

	// key�� ���� ��� t�� Ž��
	while (t != NULL && t->data.bt != key.bt)
	{
		p = t;
		t = (key.bt < p->data.bt) ? p->left : p->right;
	}
	// Ž���� ����� ����
	if (t == NULL)
	{
		printf("key is not in the three");
		return;
	}
	// ù��° ��� : �ܸ� ����� ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else
			*root = NULL;
	}
	// �ι�° ��� : �ϳ��� �ڽĸ� ������ ���
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

	// ����° ��� : �� ���� �ڽ��� ������ ���
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

