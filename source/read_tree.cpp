// do it in ANA_BinTree and include pointer to data_handler

#include "../include/read_tree.h"

#define SKIP_SPACES(input, input_shift) \
    while (input [*input_shift] == ' ') \
    {                                   \
        ++(*input_shift);               \
    }                                   \

static char*
OpenInputFile (const char* const input_file_name);

static void
FillNewData (      char* const new_data,
             const char* const input,
             size_t*     const input_shift);

ANA_BinTree*
ReadTreeFromFile (ANA_BinTree* const tree,
                  const char * const input_file_name)
{
    char* const input = OpenInputFile (input_file_name);
    if (!input)
    {
        return nullptr;
    }

    size_t input_shift = 0;

    tree->root = ReadNode (tree, nullptr, input, &input_shift);

    free (input);

    return tree;
}

ANA_BinTree_node*
ReadNode (ANA_BinTree*      const tree,
          ANA_BinTree_node* const parent,
          const char*       const input,
          size_t*           const input_shift)
{
    SKIP_SPACES (input, input_shift);

    if (input [*input_shift] == '(')
    {
        ++(*input_shift);
        SKIP_SPACES (input, input_shift);
    }

    else if (strncmp (input + *input_shift, "nil", strlen ("nil")) == 0)
    {
        *input_shift += strlen ("nil");
        SKIP_SPACES (input, input_shift);

        return nullptr;
    }

    char* const new_data = (char*) calloc (sizeof (char), DESCRIPTION_MAX_LEN);
    tree->allocated_data [tree->allocated_data_number++] = new_data;

    FillNewData (new_data, input, input_shift);

    fprintf (stderr, "%s\n", new_data);

    ANA_BinTree_node* const new_node =
        ANA_BinTree_CtorNode (new_data, nullptr, nullptr, parent);

    new_node->left  = ReadNode (tree, new_node, input, input_shift);
    new_node->right = ReadNode (tree, new_node, input, input_shift);

    SKIP_SPACES (input, input_shift);

    if (input [*input_shift] !=  ')')
    {
        fprintf (stderr, "Wrong file input! No closing bracket\n");
        return nullptr;
    }

    else
    {
        (*input_shift)++;
        return new_node;
    }
}

static void
FillNewData (      char* const new_data,
             const char* const input,
             size_t*     const input_shift)
{
    size_t      new_data_index = 0;

    if (input [*input_shift] != '\"')
    {
        fprintf (stderr, "Wrong file input: %d!\n", input [*input_shift]);
        return;
    }
    else
    {
        ++(*input_shift);
    }

    for (new_data_index = 0; input [(*input_shift)] != '\"'; ++new_data_index)
    {
        new_data [new_data_index] = input [*input_shift];
        (*input_shift)++;
    }

    (*input_shift)++;
    SKIP_SPACES (input, input_shift);
    new_data [new_data_index] = '\0';
}

static char*
OpenInputFile (const char* const input_file_name)
{
    assert (input_file_name);

    FILE* input_file = fopen (input_file_name, "rb");
    if (!input_file)
    {
        perror ("Unable to open input file with tree");
        return nullptr;
    }

    fseek  (input_file, 0, SEEK_END);
    size_t input_len = (size_t) ftell(input_file);
    fseek  (input_file, 0, SEEK_SET);

    char* const input = (char*) calloc (sizeof (char), input_len);

    fread (input, sizeof (char), input_len, input_file);

    fclose (input_file);

    return input;
}
