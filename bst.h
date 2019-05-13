#ifndef _BST_H_
#define _BST_H_
#include<iostream>
#include<stdio.h>

//----------------------------------------------------------------------------------------------
// User Defined Datatypes
//----------------------------------------------------------------------------------------------

// Tree node structure
typedef struct Node_tag
{
    int val;
    struct Node_tag *left;
    struct Node_tag *right;
}Node_t;


/* BST traversal types */
enum traversal_en
{
    INORDER,
    PREORDER,
    POSTORDER,
    LEVELORDER,
    LEVELORDER_LEVEL_BY_LEVEL
};

//----------------------------------------------------------------------------------------------
// Binary Search Tree Class
//----------------------------------------------------------------------------------------------
class BST
{
private:
    // Member variables
    size_t m_numElements;
    Node_t *m_root;

    // Private functions
    Node_t *Insert(int data, Node_t * root);
    Node_t* Delete(int data, Node_t *root);
    bool IsValuePresent(int val, Node_t *root);
    void FreeMemory(Node_t *root);
    void InOrderDisplay(Node_t * root);
    void PreOrderDisplay(Node_t * root);
    void PostOrderDisplay(Node_t * root);
    void LevelOrderDisplay(Node_t *root);
    int Height(Node_t *root);
    int max(int x, int y);

public:
    BST();
    ~BST();
    Node_t* Insert(int data);
    bool Delete(int data);
    void Display(traversal_en traversal);
    bool IsValuePresent(int val);
    size_t Size();
    int Height();
};

#endif