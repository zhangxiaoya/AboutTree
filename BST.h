
#ifndef RECOVERTREE_BST_H
#define RECOVERTREE_BST_H

#include <string>
#include "TreeNode.h"

using std::string;

class BST
{
public:

    BST(TreeNode* _root = nullptr);

    void dumpDot(const string &fileName);


    void dumpDot(const string &fileName, TreeNode *t);


    string dumpDotImp(TreeNode *t);

private:
    TreeNode* root;

};


#endif //RECOVERTREE_BST_H
