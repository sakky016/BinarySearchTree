#include"bst.h"
#include"random.h"

//----------------------------------------------------------------------------------------------
// Configurations
//----------------------------------------------------------------------------------------------
#define MANUAL_TEST
const int NUMBER_RANGE = 500;
const int REPEATS = 100;

//----------------------------------------------------------------------------------------------
// M A I N
//----------------------------------------------------------------------------------------------
int main()
{
    RandomGenerator rng;

    {
        BST bst;

#ifdef MANUAL_TEST
        bst.Insert(50);
        bst.Insert(40);
        bst.Insert(30);
        bst.Insert(45);
        bst.Insert(78);
        bst.Insert(88);
        bst.Insert(80);
        bst.Insert(90);

        cout << bst.IsValuePresent(50) << endl;
        cout << bst.IsValuePresent(80) << endl;
        cout << bst.IsValuePresent(90) << endl;
        cout << bst.IsValuePresent(10) << endl;

        bst.Delete(45);
        bst.Delete(30);
        bst.Delete(10);
        bst.Delete(78);
        bst.Delete(88);
#else
        for (int i = 0; i < REPEATS; i++)
        {
            int val = rng.generateRandomNumber(NUMBER_RANGE);
            printf("\nInsert [%d]\n", val);
            bst.Insert(val);
        }
#endif

        printf("\n");
        printf("BST size   : %lu elements\n", bst.Size());
        printf("\n");
        printf("BST height : %d\n", bst.Height());

        printf("\n\nIn Order:\n");
        bst.Display(INORDER);
        printf("\n\nPre Order:\n");
        bst.Display(PREORDER);
        printf("\n\nPost Order:\n");
        bst.Display(POSTORDER);
        printf("\n\nLevel Order:\n");
        bst.Display(LEVELORDER);

    }//End of scope of bst variable

    getchar();
}