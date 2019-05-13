#include"bst.h"
#include<queue>

//----------------------------------------------------------------------------------------------
// @name                    : BST
//
// @description             : Constructor
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
BST::BST()
{
    m_root = nullptr;
    m_numElements = 0;
}

//----------------------------------------------------------------------------------------------
// @name                    : ~BST
//
// @description             : Destructor
//                            Clears the memory occupied by each node in the BST.
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
BST::~BST()
{
    printf("\n\n*** FreeMemory called. Deallocating memory of %lu nodes\n", this->Size());
    FreeMemory(m_root);
}

//----------------------------------------------------------------------------------------------
// @name                    : FreeMemory
//
// @description             : Deallocate memory allocated to all nodes of the tree by doing a
//                            post-order traversal.
//
// @param root              : Root node
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
void BST::FreeMemory(Node_t *root)
{
    if (root == nullptr)
    {
        return;
    }

    FreeMemory(root->left);
    FreeMemory(root->right);
    delete root;
}

//----------------------------------------------------------------------------------------------
// @name                    : Insert
//
// @description             : Inserts a given data to the BST. This function will be used
//                            outside the class to insert values into the BST.
//
// @param data              : Data (integral value) to be inserted
//
// @returns                 : Address of root node.
//----------------------------------------------------------------------------------------------
Node_t* BST::Insert(int data)
{
    return Insert(data, m_root);
}

//----------------------------------------------------------------------------------------------
// @name                    : Insert
//
// @description             : Inserts a given data to the BST. This funciton is not supposed to 
//                            be accessible outside the class.
//
// @param root              : Root node of the Binary Search Tree.
// @param data              : Data (integral value) to be inserted
//
// @returns                 : Address of root node.
//----------------------------------------------------------------------------------------------
Node_t* BST::Insert(int data, Node_t *root)
{
    if (root == nullptr)
    {
        root = new Node_t;
        root->val = data;
        root->left = nullptr;
        root->right = nullptr;

        if (m_root == nullptr)
        {
            printf("  Adding at root\n");
            m_root = root;
        }

        m_numElements++;

        // Tree is empty, insert node at root
        printf("  Inserted at 0x%lu\n", root);
    }
    else if (data < root->val)
    {
        // Insert to left of current node
        printf("  Inserting %d to left of %d\n", data, root->val);
        root->left = Insert(data, root->left);

    }
    else if(data > root->val)
    {
        // Insert to right of current node
        printf("  Inserting %d to right of %d\n", data, root->val);
        root->right = Insert(data, root->right);
    }
    else
    {
        printf("  Value [%d] already present\n", data);
    }


    return root;
}

//----------------------------------------------------------------------------------------------
// @name                    : Delete
//
// @description             : Deletes a given node from BST. This is NOT exposed outside the class
//
// @param val               : Value to delete
// @param root              : Root node.
//
// @returns                 : Pointer to node
//----------------------------------------------------------------------------------------------
Node_t* BST::Delete(int data, Node_t *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (data < root->val)
    {
        // Look in left subtree
        root->left = Delete(data, root->left);
    }
    else if (data > root->val)
    {
        // Look in right subtree
        root->right = Delete(data, root->right);
    }
    else
    {
        // Value found, delete this node.
    }

    return root;
}

//----------------------------------------------------------------------------------------------
// @name                    : Delete
//
// @description             : Deletes a given node from BST. 
//
// @param val               : Value to delete
//
// @returns                 : true if data was found and deleted, false otherwise.
//----------------------------------------------------------------------------------------------
bool BST::Delete(int data)
{
    size_t initialSize = this->Size();
    this->Delete(data, m_root);
    size_t finalSize = this->Size();
    if (initialSize != finalSize)
    {
        printf("Deleted %d\n", data);
        return true;
    }

    printf("%d not found!\n", data);
    return false;
}

//----------------------------------------------------------------------------------------------
// @name                    : IsValuePresent
//
// @description             : Checks if a given value is present in the BST. NOT exposed 
//                            outside the class.
//
// @param val               : Value to search
// @param root              : Root node.
//
// @returns                 : true if found, false otherwise
//----------------------------------------------------------------------------------------------
bool BST::IsValuePresent(int val, Node_t *root)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (val == root->val)
    {
        return true;
    }
    else if (val < root->val)
    {
        return IsValuePresent(val, root->left);
    }
    else if (val > root->val)
    {
        return IsValuePresent(val, root->right);
    }
}

//----------------------------------------------------------------------------------------------
// @name                    : IsValuePresent
//
// @description             : Checks if a given value is present in the BST
//
// @param val               : Value to search
//
// @returns                 : true if found, false otherwise
//----------------------------------------------------------------------------------------------
bool BST::IsValuePresent(int val)
{
    return IsValuePresent(val, m_root);
}

//----------------------------------------------------------------------------------------------
// @name                    : Display
//
// @description             : Display nodes in the BST.
//
// @param traversal         : Parameter specifying the type of traversal to be used
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
void BST::Display(traversal_en traversal)
{
    switch (traversal)
    {
    case INORDER:
        InOrderDisplay(m_root);
        break;
    case PREORDER:
        PreOrderDisplay(m_root);
        break;
    case POSTORDER:
        PostOrderDisplay(m_root);
        break;
    case LEVELORDER:
        LevelOrderDisplay(m_root);
        break;
    default:
        printf("Invalid traversal specified!\n");
    }
}

//----------------------------------------------------------------------------------------------
// @name                    : InOrderDisplay
//
// @description             : Display nodes in the BST in order.
//                            
// @param root              : Root node
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
void BST::InOrderDisplay(Node_t * root)
{
    if (root == nullptr)
    {
        return;
    }

    InOrderDisplay(root->left);
    printf("%d ", root->val);
    InOrderDisplay(root->right);
}

//----------------------------------------------------------------------------------------------
// @name                    : PreOrderDisplay
//
// @description             : Display nodes in the BST in pre-order.
//                            
// @param root              : Root node
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
void BST::PreOrderDisplay(Node_t * root)
{
    if (root == nullptr)
    {
        return;
    }

    printf("%d ", root->val);
    PreOrderDisplay(root->left);
    PreOrderDisplay(root->right);
}

//----------------------------------------------------------------------------------------------
// @name                    : PostOrderDisplay
//
// @description             : Display nodes in the BST in post-order.
//                            
// @param root              : Root node
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
void BST::PostOrderDisplay(Node_t * root)
{
    if (root == nullptr)
    {
        return;
    }

    PostOrderDisplay(root->left);
    PostOrderDisplay(root->right);
    printf("%d ", root->val);
}

//----------------------------------------------------------------------------------------------
// @name                    : LevelOrderDisplay
//
// @description             : Displays elements of the BST level-by-level
//                            
// @param root              : Root node
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
void BST::LevelOrderDisplay(Node_t *root)
{
    std::queue<Node_t *> nodeQueue;
    if (root == nullptr)
    {
        return;
    }

    // We use a queue to keep track of the nodes whose values
    // have to be printed at each level
    nodeQueue.push(root);
    nodeQueue.push(nullptr); // Identifier for level

    while (!nodeQueue.empty())
    {
        Node_t *node = nodeQueue.front();
        if (node)
        {
            // Prints the node value
            printf("%d ", node->val);

            if (node->left)
                nodeQueue.push(node->left);

            if (node->right)
                nodeQueue.push(node->right);
        }
        else if (node == nullptr && nodeQueue.size() == 1)
        {
            // We have covered all the nodes, the last value
            // remaining in nodeQueue is a nullptr, ignore it.
            break;
        }
        else
        {
            // Prints level identifier (\n in this case)
            printf("\n");
            nodeQueue.push(nullptr);
        }
        
        // This node's value has been printed, remove it 
        // from the queue
        nodeQueue.pop();
        
    }
}

//----------------------------------------------------------------------------------------------
// @name                    : Size
//
// @description             : Returns number of nodes in the tree.
//
// @returns                 : Nothing
//----------------------------------------------------------------------------------------------
size_t BST::Size()
{
    return m_numElements;
}

//----------------------------------------------------------------------------------------------
// @name                    : Height
//
// @description             : Returns height tree.
//
// @returns                 : int
//----------------------------------------------------------------------------------------------
int BST::Height()
{
    return this->Height(m_root);
}

//----------------------------------------------------------------------------------------------
// @name                    : Height
//
// @description             : Returns height tree. Not exposed outside this class
//
// @param root              : root node
//
// @returns                 : int
//----------------------------------------------------------------------------------------------
int BST::Height(Node_t *root)
{
    if (root == nullptr)
    {
        // Height of an empty tree is -1 by convention
        return -1;
    }

    return max(Height(root->left), Height(root->right)) + 1;
}

//----------------------------------------------------------------------------------------------
// @name                    : max
//
// @description             : Returns greater of the 2 values.
//
// @returns                 : int
//----------------------------------------------------------------------------------------------
int BST::max(int x, int y)
{
    return (x > y) ? x : y;
}