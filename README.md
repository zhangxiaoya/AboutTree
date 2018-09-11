# AboutTree
How to recover Binary tree use only pre-order visit list and post-order visit list.
给定一个二叉树的先序遍历序列和中序遍历序列,或者给定一个二叉树的中序遍历序列和后序遍历序列,都能恢复出唯一的一个二叉树(前提是这些序列都是有效的).给定一颗二叉树的线序遍历序列和后序遍历序列,能不能恢复出一颗唯一的二叉树,之前按照教科书的学到的东西,答案是不能,但是这种回到是不严禁的,应该说不一定,有可能恢复唯一的二叉树,也有可能恢复出多种可能的二叉树.

## 先序遍历序列 和 后序遍历序列可以恢复出多少种二叉树

从先序+中序序列中或者从中序+后序序列恢复出二叉树,这两种问题从本科就接触,也很容易能够写出代码,原理也很简单.

其实,从先序+后序序列中也能恢复出一颗唯一的二叉树,只不过是这里添加了条件限制,条件就是,这颗二叉树必须是没有出度为1的节点,也就是说所有的节点,要么是叶子节点,要么必须有两个子节点(左右子树).
这个原因是,如果存在只有左子树或者又子树的节点,那么,无论是左子树还是右子树,先序遍历序列和后序遍历序列的顺序都不会改变,但是如果有两个子树,那么先序和后序肯定是不同的.

比如下图这个只有左子树,先序遍历和后序遍历分别是AB和BA,但是如果把它换成只有右子树,先序遍历和后序遍历的顺序还是AB和BA.

1. 只有左子树

![](https://github.com/zhangxiaoya/AboutTree/blob/master/scripts/leftChildOnly.png)

2. 只有右子树

![](https://github.com/zhangxiaoya/AboutTree/blob/master/scripts/rightChildOnly.png)

但是如果是左右子树都有的话,比如下面的这个二叉树,先序遍历序列是ABC,后序遍历序列是BCA,可以直接确定A是根节点,先序序列肯定是先根,再左,后右;而后序的顺序是先左,再右,后根.可以看出,先序中的根节点右侧的节点可能是左子树的根节点(左右子树都存在的情况);在后序序列中,根节点的右侧第一个节点可能是右子树的根节点(左右子树都存在的情况).在先序序列中,左子树根节点的位置在右子树根节点位置的左侧,在后序序列中,右子树根节点的位置,在左子树根节点位置的右侧(不一定挨着).这样的先后顺序是唯一确定的,然后迭代到叶子节点,能确认唯一的二叉树.

3. 左右子树都有

![](https://github.com/zhangxiaoya/AboutTree/blob/master/scripts/leftAndRightChild.png)

知道了这个规律,其实也就容易知道多少中可能的二叉树了,每一个出度为1的节点,都会有两种可能,要么是左子树,要么是右子树.假设有n个节点,其中m个节点出度为1的节点,那么就有2的m次方种可能二叉树.

出度为1的节点个数是 n1,出度为2的节点个数为n2, 叶子节点个数为n0. 树中总的边数是N,每个出度会有一条边,所以, N = n1 + 2 * n2.

另外,除了根节点,每一个节点都有一个边连到入度,因此, N = n1 + n2 + n0  - 1.那么根据这个公式可以得到,n2=n0 - 1.如果能求出叶子节点个数,其他节点个数也就能求出来了,二叉树种类也就知道了.但是似乎不是很容易,下面我用直接递归的方式,计算度为1的个数,并顺便计算出所有的可能.

先序序列中根节点右侧的节点,如果与后序序列中根节点左侧的节点相同,那么说明这个根节点只有一个子树,其出度为1.

如图,表示下面的一种可能的二叉树

![](https://github.com/zhangxiaoya/AboutTree/blob/master/scripts/sample.png)

> 图是用的Graphvis画的,然后参考了下面的文章,使用了binarytree,让图变得更好看一些.在scripts文件家中,有dot脚本.使用命令 `dot sample.dot| gvpr -c -f binarytree.gvpr| neato -n -Tpng -o sample.png`来生成图片.

```
#include <iostream>
#include <string>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

    return 0;
}
```

答案是8

## 参考
1. [如何用graphvis画二叉树](https://blog.csdn.net/theonegis/article/details/71772334)
