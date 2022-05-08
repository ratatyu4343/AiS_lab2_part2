#include "BTree.h"
#include <iostream>
//-------------public methods------------------------
BTree::BTree(double* arr = nullptr, int n = 0, int t = 2)
{
    this->t = t > T_MAX ? T_MAX : t >= 2 ? t : T_MAX;
    for(int i = 0; i < n; i++)
    {
        insert_item(arr[i]);
    }
}
//inserting item
void BTree::insert_item(double key)
{
    if(!head)
    {
        head = new TreeNode(1, true);
        head->keys[0] = key;
        return;
    }
    TreeNode* node = head;
    if(node->n == 2*t - 1)
    {
        head = new TreeNode(0, false);
        head->ids[0] = node;
        split_child(head, 0, node);
        insert_not_full(head, key);
    }
    else
    {
        insert_not_full(node, key);
    }
}
//deleting item
void BTree::delete_node(double key)
{
    TreeNode* r = head;
    if(head)
    if(head->n == 1)
    {
        TreeNode* y = head->ids[0];
        TreeNode* z = head->ids[1];
        if(y)
            if(y->n == this->t - 1 && z->n == this->t - 1)
            {
                marge(head, 1, y, z);
                head = y;
                delete r;
                delete_non(y, key);
            }
            else
                delete_non(r, key);
        else
        {
            delete head;
            head = nullptr;
        }
    }
    else
    {
        delete_non(r, key);
    }
}
//searching item
std::pair<TreeNode*, int> BTree::search_item(double key)
{
    if(head)
        return tree_search(head, key);
    else
        return std::pair<TreeNode*, int>(nullptr, -1);
}
//showing item
void BTree::show_item(TreeNode* node)
{
    for(int i = 0; i < node->n; i++)
    {
        std::cout << node->keys[i] << "\t";
    }
    std::cout<<"\n";
}

//--------------------private methods----------------------
//for searching item
std::pair<TreeNode*,int> BTree::tree_search(TreeNode* node, double key)
{
    int i = 0;
    while(i < node->n && key > node->keys[i])
        i++;
    if(i < node->n && key == node->keys[i])
        return std::pair<TreeNode*,int>(node, i);
    if(node->leaf)
        return std::pair<TreeNode*,int>(nullptr, -1);
    else
        return tree_search(node->ids[i], key);
}

//splitting items
void BTree::split_child(TreeNode* x, int i, TreeNode* y)
{
    TreeNode* z = new TreeNode(this->t - 1, y->leaf);
    y->n = this->t - 1;
    for(int j = 0; j < this->t - 1; j++)
    {
        z->keys[j] = y->keys[j+this->t];
    }
    if(!y->leaf)
    {
        for(int j = 0; j < t; j++)
        {
            z->ids[j] = y->ids[j+this->t];
        }
    }
    for(int j = x->n; j > i; j--)
    {
        x->ids[j] = x->ids[j-1];
    }
    x->keys[i] = y->keys[this->t-1];
    for(int j = x->n + 1; j > i + 1; j--)
    {
        x->ids[j] = x->ids[j - 1];
    }
    x->ids[i+1] = z;
    x->n += 1;
}

//for insereting
void BTree::insert_not_full(TreeNode* x, double key)
{
    int i = x->n - 1;
    if(x->leaf)
    {
        while(i >= 0 && key < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->n += 1;
    }
    else
    {
        while(i >= 0 && key < x->keys[i])
            i--;
        i++;
        if(x->ids[i]->n == 2*this->t - 1)
        {
            split_child(x, i, x->ids[i]);
            if(x->keys[i] < key)
            {
                i++;
            }
        }
        insert_not_full(x->ids[i], key);
    }
}

//-------------for deleting--------------------
double BTree::prev(TreeNode* node)
{
    TreeNode* x = node;
    int i = node->n;
    while(!x->leaf)
    {
        x = x->ids[i];
        i = x->n;
    }
    return x->keys[i - 1];
}

double BTree::next(TreeNode* node)
{
    TreeNode* x = node;
    while(!x->leaf)
    {
        x = x->ids[0];
    }
    return x->keys[0];
}

void BTree::shift_right(TreeNode* x, int i, TreeNode* y, TreeNode* z)
{
    int j = z->n;
    while(j > 0)
    {
        z->keys[j] = z->keys[j-1];
        j--;
    }
    z->keys[0] = x->keys[i - 1];
    x->keys[i - 1] = y->keys[y->n - 1];
    z->n++;
    if(!z->leaf)
    {
        j = z->n;
        while(j > 0)
        {
            z->ids[j] = z->ids[j - 1];
        }
        z->ids[0] = y->ids[y->n];
    }
    y->n--;
}

void BTree::shift_left(TreeNode* x, int i, TreeNode* y, TreeNode* z)
{
    y->n++;
    y->keys[y->n - 1] = x->keys[i - 1];
    x->keys[i - 1] = z->keys[0];
    z->n--;
    int j = 0;
    while(j < z->n)
    {
        z->keys[j] = z->keys[j + 1];
        j++;
    }
    if(!z->leaf)
    {
        y->ids[y->n] = z->ids[0];
        j = 0;
        while(j <= z->n)
        {
            z->ids[j] = z->ids[j + 1];
            j++;
        }
    }
}

void BTree::marge(TreeNode* x, int i, TreeNode* y, TreeNode* z)
{
    y->n = 2*this->t - 1;
    for(int j = this->t; j < 2*this->t - 1; j++)
        y->keys[j] = z->keys[j - this->t];
    y->keys[t - 1] = x->keys[i - 1];
    if(!y->leaf)
    {
        for(int j = this->t; j <= 2*this->t - 1; j++)
            y->ids[j] = z->ids[j - this->t];
    }
    for(int j = i; j < x->n; j++)
    {
        x->keys[j - 1] = x->keys[j];
    }
    for(int j = i; j < x->n; j++)
    {
        x->ids[j] = x->ids[j + 1];
    }
    x->n--;
    delete z;
}

void BTree::delete_non(TreeNode* x, double key)
{
    TreeNode* y = 0;
    TreeNode* z = 0;
    int i = 0;
    if(x->leaf)
    {
        while(i < x->n && key > x->keys[i])
            i++;
        if(key == x->keys[i])
        {
            x->n--;
            for(int j = i; j < x->n; j++)
            {
                x->keys[j] = x->keys[j + 1];
            }
        }
    }
    else
    {
        while(i < x->n && key > x->keys[i])
            i++;
        y = x->ids[i];
        if(i < x->n)
            z = x->ids[i + 1];
        if(key == x->keys[i])
        {
            if(y->n > this->t - 1)
            {
                int k0 = prev(y);
                delete_non(y, k0);
                x->keys[i] = k0;
            }
            else if(z->n > this->t - 1)
            {
                int k0 = next(z);
                delete_non(z, k0);
                x->keys[i] = k0;
            }
            else
            {
                marge(x, i + 1, y, z);
                delete_non(y, key);
            }
        }
        else
        {
            TreeNode* p = 0;
            if(i > 0)
                p = x->ids[i - 1];
            if(y->n == this->t-1)
            {
                if(i > 0 && p->n > this->t - 1)
                    shift_right(x, i, p, y);
                else if(i < x->n && z->n > this->t - 1)
                {
                    shift_left(x, i + 1, y, z);
                }
                else if(i > 0)
                {
                    marge(x, i, p, y);
                    y = p;
                }
                else
                    marge(x, i+1, y, z);

            }
            delete_non(y, key);
        }
    }
}
