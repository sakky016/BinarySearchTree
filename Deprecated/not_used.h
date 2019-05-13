#ifndef _BST_H_
#define _BST_H_
#include<iostream>
#include<queue>
#include<map>

using namespace std;

/* BST node structure */
template <typename T>
struct node_t
{
    T data;
    struct node_t *left;
    struct node_t *right;
};

/* BST traversal types */
enum traversal_t
{
    INORDER,
    PREORDER,
    POSTORDER,
    LEVELORDER,
    LEVELORDER_LEVEL_BY_LEVEL
};

/* Binary Search Tree class */
template <typename T>
class BST
{
    private:
        /* MEMBER VARIABLES */
        node_t<T> *m_pRoot;
        unsigned int m_Size;

        /* PRIVATE FUNCTIONS that can be accessed only by member functions */

        /* Insert */
        node_t<T>* insertInBST(node_t<T> *root, T val)
        {
            if (root == NULL)
            {
                printf(" Inserted\n");
                node_t<T> *newnode = new node_t<T>;
                newnode->data = val;
                newnode->left  = NULL;
                newnode->right = NULL;
                root = newnode;
                m_Size++;
            }
            else if (val < root->data)
            {
                printf(" Check %d, go left\n", root->data);
                root->left = insertInBST(root->left, val);
            }
            else
            {
                printf(" Check %d, go right\n", root->data);
                root->right = insertInBST(root->right, val);
            }

            return root;
        }

        /* Returns the minimum value node */
        node_t<T> *findMinValueNode(node_t<T> *root)
        {
            node_t<T> *minValNode = root;

            if (root == NULL)
            {
                return root;
            }


            T minVal = root->data;
            root = root->left;

            while (root != NULL)
            {
                if (root->data < minVal)
                {
                    minVal = root->data;
                    minValNode = root;
                }

                /* In a BST, the lower value can only be to the
                   left of the current node */
                root = root->left;
            } /* End of while loop */

            return minValNode;
        }

        /* Delete a node with value 'val' from BST pointed to by 'root' */
        node_t<T>* deleteFromBST(node_t<T> *root, T val)
        {
            if (root == NULL)
            {
                return root;
            }

            if (val < root->data)
            {
                root->left = deleteFromBST(root->left, val);
            }
            else if (val > root->data)
            {
                root->right = deleteFromBST(root->right, val);
            }
            else
            {
                /* Found the value, delete it */

                /* Case 1: node to be deleted is leaf node */
                if ((root->left == NULL) && (root->right == NULL))
                {
                    delete root;
                    m_Size--;
                    root = NULL;
                }

                /* Case 2: node to be deleted has 1 child */
                else if (root->left == NULL)
                {
                    node_t<T> *tmp = root->right;
                    delete root;
                    m_Size--;
                    root = tmp;
                }
                else if (root->right == NULL)
                {
                    node_t<T> *tmp = root->left;
                    delete root;
                    m_Size--;
                    root = tmp;
                }

                /* Case 3: node to be deleted has 2 children */
                else
                {
                    /* Find the minimum value node in the right subtree */
                    node_t<T> *tmp = findMinValueNode(root->right);

                    /* Copy the data of the minimum value node into current node */
                    root->data = tmp->data;
                    printf(" Minimum value in right subtree of node to be deleted: %d\n", root->data);

                    /* Delete the node with duplicate value */
                    root->right = deleteFromBST(root->right, root->data);

                }
            }

            return root;
        }


        void printRootAndLeafOfBST(node_t<T> *root)
        {
            bool found = false;
            if (root == NULL)
            {
                return;
            }

            /* Check if this node has a left child and 
               that child is is a leaf node */
            if (root->left &&
                !root->left->left &&
                !root->left->right)
            {
                printf("%d ", root->left->data);
                found = true;
            }

            /* Check if this node has a right child and 
               that child is is a leaf node */
            if (root->right &&
                !root->right->left &&
                !root->right->right)
            {
                printf("%d ", root->right->data);
                found = true;
            }

            if (found)
            {
                /* If either left/right child is present, then 
                   we need to print its root's data also. */
                printf(" %d\n", root->data);
            }
            else
            {
                printRootAndLeafOfBST(root->left);
                printRootAndLeafOfBST(root->right);
            }
        }

        /* Find */
        bool findNodeInBST(node_t<T> *root, T val)
        {
            if (root == NULL)
            {
                return false;
            }
            else if (root->data == val)
            {
                return true;
            }
            else if (val < root->data)
            {
                printf(" Check %d, go left\n", root->data);
                findNodeInBST(root->left, val);
            }
            else
            {
                printf(" Check %d, go right\n", root->data);
                findNodeInBST(root->right, val);
            }

        }

        void InorderDisplay(node_t<T> *root)
        {
            if (root == NULL)
            {
                return;
            }

            InorderDisplay(root->left);
            printf("%d ", root->data);
            InorderDisplay(root->right);
        }

        void PreOrderDisplay(node_t<T> *root)
        {
            if (root == NULL)
            {
                return;
            }

            printf("%d ", root->data);
            PreOrderDisplay(root->left);
            PreOrderDisplay(root->right);
        }

        void PostOrderDisplay(node_t<T> *root)
        {
            if (root == NULL)
            {
                return;
            }

            PostOrderDisplay(root->left);
            PostOrderDisplay(root->right);
            printf("%d ", root->data);
        }

        void LevelOrderDisplay(node_t<T> *root)
        {
            if (root == NULL)
            {
                return;
            }

            queue<node_t<T> *> Q;
            Q.push(root);

            while (!Q.empty())
            {
                node_t<T> *current = Q.front();
                int val = current->data;
                printf("%d ", val);

                if (current->left)
                {
                    Q.push(current->left);
                }

                if (current->right)
                {
                    Q.push(current->right);
                }

                Q.pop();
            }
        }

        void LevelOrderDisplayLevelByLevel(node_t<T> *root)
        {
            map<int, int> levelVal;
            int level = 0;

            if (root == NULL)
            {
                return;
            }

            queue<node_t<T> *> Q;
            Q.push(root);
            /* Enqueue a NULL to mark a level */
            Q.push(NULL);

            while (!Q.empty())
            {
                node_t<T> *current = Q.front();

                if (current == NULL && Q.size() == 1)
                {
                    /* If the queue has only a NULL left, 
                       it means we have covered all the nodes */
                    break;
                }
                else if (current == NULL)
                {
                    level++;
                    printf("\n");
                    Q.push(NULL);
                }
                else
                {

                    int val = current->data;
                    printf("%d ", val);
                    levelVal[level] = val;

                    if (current->left)
                    {
                        Q.push(current->left);
                    }

                    if (current->right)
                    {
                        Q.push(current->right);
                    }
                }
                
                Q.pop();
            }

            /* Rightmost node: START */
            int i = 0;
            printf("\n\nRightmost element of level:\n");
            while (i <= level)
            {
                printf("%d\n", levelVal[i]);
                i++;
            }
            printf("\n");
            /* Rightmost node: END */
        }

        /* Use post order traversal to delete each node of 
           the BST */
        void freeBST(node_t<T> *root)
        {
            if (root == NULL)
            {
                return;
            }

            freeBST(root->left);
            freeBST(root->right);
            printf(" Freeing %d\n", root->data);
            delete root;
            m_Size--;
        }

        /* Returns the larger of val1 and val2 */
        T max(T val1, T val2)
        {
            if (val1 > val2)
            {
                return val1;
            }
            else
            {
                return val2;
            }
        }

        /* Calculate height of tree by recursion. Height is the number
           of edges (NOT nodes) from root to the leaf node of 
           the longest subtree */
        int heightOfBST(node_t<T> *root)
        {
            if (root == NULL)
            {
                /* Height of an empty tree is -1 by convention */
                return -1;
            }

            return max(heightOfBST(root->left), heightOfBST(root->right)) + 1;
        }

    public:
        /* Constructor */
        BST()
        {
            m_pRoot = NULL;
            m_Size = 0;
            printf("BST created\n");
        }

        /* Destructor */
        ~BST()
        {
            printf("\nFreeing memory used by BST...\n");
            freeBST(m_pRoot);
            if (m_Size == 0)
            {
                printf(" BST destroyed\n");
            }
            else
            {
                printf(" BST COULD NOT be freed properly. Unfreed count: %d\n", m_Size);
            }
        }


        /* Insert 'val' in BST */
        void insertNode(T val)
        {
            m_pRoot = insertInBST(m_pRoot, val); 
        }

        /* Find and delete 'val' from BST, else return false.
           Returns true if val was found and deleted,
           false otherwise */
        bool deleteNode(T val)
        {
            printf("Deleting [%d]...\n", val);
            unsigned int initialCount = m_Size;
            printf(" Initial number of nodes: %u\n", initialCount);
            m_pRoot = deleteFromBST(m_pRoot, val);
            unsigned int finalCount = m_Size;
            printf(" Final number of nodes: %u\n", finalCount);
            if (initialCount != finalCount)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /* Find a value in BST */
        bool findNode(T val)
        {
            bool retval = false;
            printf("Searching [%d]...\n", val);
            retval = findNodeInBST(m_pRoot, val);
            return retval;
        }

        /* Display values in tree */
        void display(enum traversal_t type)
        {
            switch (type)
            {
                case INORDER:
                    InorderDisplay(m_pRoot);
                    break;
                case PREORDER:
                    PreOrderDisplay(m_pRoot);
                    break;
                case POSTORDER:
                    PostOrderDisplay(m_pRoot);
                    break;
                case LEVELORDER:
                    LevelOrderDisplay(m_pRoot);
                    break;
                case LEVELORDER_LEVEL_BY_LEVEL:
                    LevelOrderDisplayLevelByLevel(m_pRoot);
                    break;

                default:
                    printf("Invalid traversal type!\n");
            }
            printf("\n");
        }

        /* Find Height of BST */
        int height()
        {
            return heightOfBST(m_pRoot);    
        }

        /* Print the leaf node and their root's value */
        void printRootAndLeafNodes()
        {
            printRootAndLeafOfBST(m_pRoot);
        }

};



#endif
