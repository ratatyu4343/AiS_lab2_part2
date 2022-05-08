#ifndef BTREE_H
#define BTREE_H
#include "TreeNode.h"
#include <utility>
#include <iostream>
class BTree
{
    public:
        BTree(double* arr, int n, int t);
        std::pair<TreeNode*, int> search_item(double key);
        void show_item(TreeNode* node);
        void insert_item(double key);
        void delete_node(double key);
    private:
        int t;
        TreeNode* head = nullptr;
        std::pair<TreeNode*, int> tree_search(TreeNode* t, double key);
        void split_child(TreeNode* x, int i, TreeNode* y);
        void insert_not_full(TreeNode* x, double key);
        double prev(TreeNode* node);
        double next(TreeNode* node);
        void shift_right(TreeNode* x, int i, TreeNode* y, TreeNode* z);
        void shift_left(TreeNode* x, int i, TreeNode* y, TreeNode* z);
        void marge(TreeNode* x, int i, TreeNode* y, TreeNode* z);
        void delete_non(TreeNode* x, double key);
};

#endif // BTREE_H
