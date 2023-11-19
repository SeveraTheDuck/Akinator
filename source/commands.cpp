#include "../include/commands.h"

static void
FillDescriptionStack (ANA_BinTree_node** found_node,
                      Stack* const       describe_stk);

static void
PrintDescription (const ANA_BinTree_node* found_node,
                        Stack* const      describe_stk);

static char*
AllocateNewObject (char** new_object,
                   char** new_difference,
                   ANA_BinTree* const tree);

static void
GetNewNodeInfo (char* const new_object,
                char* const new_difference,
                const ANA_BinTree_node* const cur_node);

static void
DeleteNewLineSymbol (char* const str);

ANA_BinTree_node*
GuessObject (ANA_BinTree* const tree)
{
    assert (tree);
    assert (tree->root);

    ANA_BinTree_node* cur_node = tree->root;
    int answer = 0;

    while (true)
    {
        printf ("%s?\n", cur_node->data);

        answer = getchar ();

        while (getchar () != '\n') {};

        if (toupper (answer) == 'Y')
        {
            if (cur_node->left == nullptr)
            {
                printf ("Again, machine has proved its superiority "
                        "above human being!\n");

                break;
            }

            cur_node = cur_node->left;
        }

        else if (toupper (answer) == 'N')
        {
            if (cur_node->right == nullptr)
            {
                GetNewNode (tree, cur_node);

                break;
            }

            cur_node = cur_node->right;
        }

        else
        {
            printf ("Wrong letter selected: %c\n"
                    "Please, type Y if answer is \"yes\" and "
                    "N if answer is \"no\"\n", answer);
        }
    }

    return cur_node;
}

ANA_BinTree_node*
GetNewNode (ANA_BinTree*      const tree,
            ANA_BinTree_node* const cur_node)
{
    assert (tree);
    assert (cur_node);

    char* new_object     = nullptr;
    char* new_difference = nullptr;

    if (!AllocateNewObject (&new_object, &new_difference, tree))
    {
        return nullptr;
    }

    GetNewNodeInfo (new_object, new_difference, cur_node);

    ANA_BinTree_node* new_left  =
        ANA_BinTree_CtorNode (new_object, nullptr, nullptr, cur_node);
    ANA_BinTree_node* new_right =
        ANA_BinTree_CtorNode (cur_node->data, nullptr, nullptr, cur_node);

    cur_node->data  = new_difference;
    cur_node->left  = new_left;
    cur_node->right = new_right;

    return cur_node;
}

static char*
AllocateNewObject (char** new_object,
                   char** new_difference,
                   ANA_BinTree* const tree)
{
    *new_object = (char*) calloc (OBJECT_NAME_MAX_LEN, sizeof (char));
    if  (!(*new_object))
    {
        perror ("new_object allocation error");
        return *new_object;
    }

    tree->allocated_data [++(tree->allocated_data_number)] =
        *new_object;

    *new_difference = (char*) calloc (DESCRIPTION_MAX_LEN, sizeof (char));
    if  (!(*new_difference))
    {
        perror ("new_difference allocation error");
        return *new_difference;
    }
    tree->allocated_data [++(tree->allocated_data_number)] =
        *new_difference;

    return *new_object;
}

static void
GetNewNodeInfo (char* const new_object,
                char* const new_difference,
                const ANA_BinTree_node* const cur_node)
{
    printf ("It seems to me, you didn't tell me something. "
            "What was it?\n");

    fgets (new_object, OBJECT_NAME_MAX_LEN, stdin);
    DeleteNewLineSymbol (new_object);

    printf ("What is the difference between %s and %s?\n",
            new_object, cur_node->data);

    fgets (new_difference, DESCRIPTION_MAX_LEN, stdin);
    DeleteNewLineSymbol (new_difference);

    /*
     * fflush (stdin) is used to avoid problems with
     * getchar () in main Akinator function when user
     * chooses the process to run.
    */
    fflush (stdin);
}

static void
DeleteNewLineSymbol (char* const str)
{
    for (size_t str_index = 0;
                ;
                str_index++)
    {
        if (str [str_index] == '\n')
        {
            str [str_index] = '\0';

            return;
        }
    }
}

void
DescribeObject (const ANA_BinTree* const tree,
                const char*        const object)
{
    assert (tree);
    assert (object);

    ANA_BinTree_node* found_node =
        FindObject (tree->root, object);

    if (!found_node)
    {
        printf ("I don't know such an object!\n");
        return;
    }

    printf ("I know what is it! %s: ", object);

    Stack describe_stk = {};
    STACK_CTOR (&describe_stk);

    FillDescriptionStack (&found_node, &describe_stk);

    PrintDescription     (found_node,  &describe_stk);

    STACK_DTOR (&describe_stk);
}

static void
FillDescriptionStack (ANA_BinTree_node** found_node,
                      Stack* const describe_stk)
{
    while ((*found_node)->parent)
    {
        if (*found_node == (*found_node)->parent->left)
        {
            StackPush (describe_stk, NODE_ANSWER_YES);
        }
        else
        {
            StackPush (describe_stk, NODE_ANSWER_NO);
        }

        *found_node = (*found_node)->parent;
    }
}

static void
PrintDescription (const ANA_BinTree_node* found_node,
                        Stack* const      describe_stk)
{
    Elem_t answer_indicator = NODE_ANSWER_NO;

    for (int32_t stack_index = (int32_t) describe_stk->data_size - 1;
                 stack_index >= 0;
               --stack_index)
    {
        StackPop (describe_stk, &answer_indicator);

        if (answer_indicator)
        {
            printf ("%s ", found_node->data);
            found_node = found_node->left;
        }
        else
        {
            printf ("not %s ", found_node->data);
            found_node = found_node->right;
        }
    }

    printf ("\n");
}

ANA_BinTree_node*
FindObject (      ANA_BinTree_node* const node,
            const char*             const object)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (strcmp (node->data, object) == 0)
    {
        return node;
    }

    ANA_BinTree_node* found_object = nullptr;

    found_object = FindObject (node->left, object);

    if (found_object)
    {
        return found_object;
    }

    found_object = FindObject (node->right, object);

    return found_object;
}

void
CompareObjects (const ANA_BinTree* const tree)
{
    char first_object  [OBJECT_NAME_MAX_LEN] = {};
    char second_object [OBJECT_NAME_MAX_LEN] = {};

    printf ("What objects dou you want to compare?");
    scanf  (ANA_BinTree_OUTPUT_F ANA_BinTree_OUTPUT_F,
            first_object, second_object);

    ANA_BinTree_node* found_first_object =
        FindObject (tree->root, first_object);

    if (!found_first_object)
    {
        printf ("First object not found. "
                "Please, check if it is correct. Return.");

        return;
    }

    ANA_BinTree_node* found_second_object =
        FindObject (tree->root, second_object);

    if (!found_second_object)
    {
        printf ("Second object not found. "
                "Please, check if it is correct. Return.");

        return;
    }

    Stack first_object_description = {};
    STACK_CTOR (&first_object_description);

    Stack second_object_description = {};
    STACK_CTOR (&second_object_description);

    FillDescriptionStack (&found_first_object,  &first_object_description);
    FillDescriptionStack (&found_second_object, &second_object_description);

    // PrintComparison (&first_object_description,
    //                  &second_object_description,
    //                  tree);
}

// static void
// PrintComparison (Stack* const first_object_description,
//                  Stack* const second_object_description,
//                  const ANA_BinTree* const tree)
// {
//     char similarities [DESCRIPRION_MAX_LEN] = {};
//     size_t similarities_index = 0;
//
//     char differences  [DESCRIPRION_MAX_LEN] = {};
//     size_t differences_index  = 0;
//
//     size_t first_index  =  first_object_description->data_size - 1;
//     size_t second_index = second_object_description->data_size - 1;
//
//     while (first_index  >= 0 &&
//            second_index >= 0)
//     {
//         if ( first_object_description->data [first_index] !=
//             second_object_description->data [second_index])
//         {
//             break;
//         }
//
//         snprintf (similarities + similarities_index, "%s",
//                   )
//     }
// }

// void
// ShowImage ()
// {
//
// }
