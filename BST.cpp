
#include <fstream>
#include <sstream>
#include "BST.h"

BST::BST(TreeNode *_root)
{
    this->root = _root;
}

void BST::dumpDot(const string &fileName)
{
    dumpDot(fileName, root);
}

void BST::dumpDot(const string &fileName, TreeNode *t)
{
    std::string begin = "\
    digraph G {\n \
    graph [ dpi = 100 ];\n \
    nodesep=0.3;\n \
    ranksep=0.2;\n \
    margin=0.1;\n \
    node [shape=circle];\n \
    edge [arrowsize=0.8];\n";

    std::string end = "}";

    std::ofstream ofs(fileName);
    if (ofs)
    {
        ofs << begin << std::endl;
        ofs << dumpDotImp(t);
        ofs << end << std::endl;
    }
    ofs.close();

}

std::string BST::dumpDotImp(TreeNode *t)
{
    string result;
    if (t)
    {
        std::ostringstream out;
        if (t->left) out << "    " << t->val << " -> " << t->left->val << ";" << std::endl;
        if (t->right) out << "    " << t->val << " -> " << t->right->val << ";" << std::endl;

        // introduce new, invisible middle nodes to re-balance the layout.
        {
            unsigned long long addr = (unsigned long long) (unsigned *) t;
            out << "    " << addr << " [label=\"\",width=.1,style=invis]" << std::endl;
            out << "    " << t->val << " -> " << addr << " [style=invis]" << std::endl;
            if (t->left || t->right)
            {
                out << "    {rank=same ";
                if (t->left)
                {
                    out << t->left->val << " -> ";
                }
                out << addr;
                if (t->right)
                {
                    out << " -> " << t->right->val;
                }
                out << " [style=invis]}" << std::endl << std::endl;
            }
        }

        result = out.str();
        // When we flatten the BST into a double linked list,
        // we should not access its left again, otherwise, it will be endless.
        // For single linked list, t->left == NULL.
        if (t->left && t->left->right != t)
            result += dumpDotImp(t->left);
        result += dumpDotImp(t->right);
    }
    return result;
}