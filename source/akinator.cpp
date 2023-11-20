#include "../include/akinator.h"

static void
EndAkinator (ANA_BinTree* const tree);

void
RunAkinator ()
{
    ANA_BinTree tree = {};
    ANA_BinTree_Ctor (&tree);

    ReadTreeFromFile (&tree);

    int32_t task_answer = 0;

    printf ("Welcome to my TreeKinator program! "
            "I wanna show you some magic! Let's see what I can do:\n"
            "    1. Guess an object that you are thinking about.\n"
            "    2. Describe an object from my database.\n"
            "    3. Compare two objects and show their similarities and "
                    "differences.\n"
            "    4. Make a picture of my database.\n"
            "    5. End the program.\n\n"
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
                ANA_BinTree_MakeTreeImage (&tree);
                break;
            }

            default:
            {
                printf ("Wrong input. Please, type the number "
                        "from 1 to 5.\n");
                break;
            }
        }

        printf ("\nPlease, type the number of task you want to do:\n");

        task_answer = getchar ();
        while (getchar() != '\n');
    }

    EndAkinator (&tree);
}

static void
EndAkinator (ANA_BinTree* const tree)
{
    ANA_BinTree_DestroySubtree (tree->root);

    for (size_t allocated_index = 0;
                allocated_index < tree->allocated_data_number;
                allocated_index++)
    {
        free (tree->allocated_data [allocated_index]);
        tree->allocated_data [allocated_index] = ANA_BinTree_POISON;
    }

    tree->allocated_data_number = 0;
}
