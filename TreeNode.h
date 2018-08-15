
#ifndef RECOVERTREE_TREENODE_H
#define RECOVERTREE_TREENODE_H

#include <cstdio>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
#endif //RECOVERTREE_TREENODE_H
