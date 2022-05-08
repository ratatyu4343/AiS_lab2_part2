#ifndef TREENODE_H
#define TREENODE_H

const int T_MAX = 3000;
class TreeNode
{
    public:
        TreeNode(int n, bool leaf);
        int n;
        bool leaf;
        double keys[T_MAX];
        TreeNode* ids[T_MAX + 1];
};

#endif // TREENODE_H
