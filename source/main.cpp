#include "../BinTree/include/ANA_BinTree_struct.h"
#include "../BinTree/include/ANA_BinTree_make_image.h"
#include "../include/commands.h"

/*
 * TODO: Read tree from file                    Result: none
 * TODO: Guess function                         Result: +
 * TODO: Find and describe function             Result: +
 * TODO: Compare function                       Result: none
 * TODO: Image open function                    Result: none
 * TODO: Everything from terminal interface     Result: + (in progress)
 *
 * OPTIONAL: pischalka
*/

int main (int /*argc*/, char** /*argv*/)
{
    ANA_BinTree tree = {};
    ANA_BinTree_Ctor (&tree, "An animal");

    tree.root->right =
        ANA_BinTree_CtorNode ("Flower",     nullptr, nullptr, tree.root);
    tree.root->left  =
        ANA_BinTree_CtorNode ("Crocodile",  nullptr, nullptr, tree.root);

    int task_answer = 0;

    printf ("Welcome to my TreeKinator program! "
            "I wanna show you some magic! Let's see what I can do:\n"
            "    1. Guess an object that you are thinking about.\n"
            "    2. Describe an object from my database.\n"
            "    3. Compare two objects and show their similarities and "
                    "differences.\n"
            "    4. Show you a picture of my database.\n"
            "    5. End the program.\n"
            "Please, type the number of task you want to do:\n");

    task_answer = getchar ();
    while (getchar() != '\n');

    while (task_answer != '5')
    {
        switch (task_answer)
        {
            case '1':
            {
                GuessObject (&tree);
                break;
            }

            case '2':
            {
                DescribeObject (&tree, "Crocodile");
                break;
            }

            case '3':
            {
                // CompareObjects ();
                break;
            }

            case '4':
            {
                // ShowImage ();
                break;
            }

            default:
            {
                printf ("Wrong input. Please, type the number "
                        "from 1 to 5.\n");
                break;
            }
        }

        printf ("Please, type the number of task you want to do:\n");

        task_answer = getchar ();
        while (getchar() != '\n');
    }

    ANA_BinTree_MakeTreeImage (&tree);

    ANA_BinTree_DestroySubtree (tree.root);

    return 0;
}
