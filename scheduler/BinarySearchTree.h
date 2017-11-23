#pragma once
#include "elementHeader.h"

typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *treeSearch(TreeNode *node, element key);
TreeNode *treeSearchMinimum(TreeNode *node);
void treeInsert_node(TreeNode **root, element key);
void treeDelete_node(TreeNode **root, element key);