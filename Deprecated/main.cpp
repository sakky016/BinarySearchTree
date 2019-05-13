#include "bst.h"

void displayBSTdata(BST<int> &tree)
{
    printf("\n");

    printf("In Order:\n");
    tree.display(INORDER);

    printf("Pre Order:\n");
    tree.display(PREORDER);

    printf("Post Order:\n");
    tree.display(POSTORDER);

    printf("Level Order:\n");
    tree.display(LEVELORDER);

    printf("Level Order level by level:\n");
    tree.display(LEVELORDER_LEVEL_BY_LEVEL);

    printf("Tree height: %d\n", tree.height());
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Specify the numbers to insert\n");
        return 0;
    }

    BST<int> tree;
    int values = argc - 1;
    int i = 1;

    while (i < argc)
    {
        printf("Inserting %d...\n", atoi(argv[i]));
        tree.insertNode(atoi(argv[i]));
        i++;
    }/* End of insertion */
    cout<<endl;
    
    printf("leaf node and their root's data:\n");
    tree.printRootAndLeafNodes();

    displayBSTdata(tree);

    while (1)
    {
        int val = 0;
        bool retval = false;

        cout<<"Enter val to find: ";
        cin>>val;
        retval = tree.findNode(val);
        if (retval == true)
        {
            printf(" %d found\n", val);
        }
        else
        {
            printf(" %d NOT found\n", val);
        }

        cout<<"\nEnter val to delete: ";
        cin>>val;
        retval = tree.deleteNode(val);
        if (retval == true)
        {
            printf(" Deleted\n");
            displayBSTdata(tree);
        }
        else
        {
            printf(" %d not found\n", val);
        }

        break;
    }/* end of while loop */


    return 0;
}
