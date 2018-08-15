#include <iostream>
#include <string>
#include "TreeNode.h"
#include "BST.h"

using namespace std;

void howManyBinaryTree(const string& preOrder, const string& postOrder, int& count)
{
    int len = preOrder.length();
    if(len == 1 || len == 0)
        return;

    char root = preOrder[0];
    char leftChild = preOrder[1];
    // 只有一个子节点,存在二义性,不能确定是左子树还是右子树,假设只有左子树
    if(leftChild == postOrder[len-2])
    {
        string leftPreOrder = preOrder.substr(1);
        string leftPostOrder = postOrder.substr(0,len-1);
        count <<= 1;
        howManyBinaryTree(leftPreOrder, leftPostOrder, count);
    }
    else
    {
        int pivot = len - 2;
        for(;pivot >= 0 ; pivot--)
        {
            if(postOrder[pivot] == preOrder[1])
                break;
        }
        string leftPreOrder = preOrder.substr(1, pivot+1);
        string leftPostOrder = postOrder.substr(0,pivot+1);
        string rightPreOrder = preOrder.substr(pivot+2);
        string rightPostOrder = postOrder.substr(pivot+1, len - (pivot+1) -1);
        howManyBinaryTree(leftPreOrder, leftPostOrder, count);
        howManyBinaryTree(rightPreOrder, rightPostOrder, count);
    }
}

int main()
{
    string preOrder = "ABDEFCHG";
    string postOrder = "DFEBGHCA";

    int count = 1;
    howManyBinaryTree(preOrder, postOrder, count);
    cout << count << endl;

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root -> left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    BST bst(root);
    bst.dumpDot("test.dot");

    return 0;
}