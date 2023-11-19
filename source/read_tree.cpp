// do it in ANA_BinTree and include pointer to data_handler

// #include "../include/read_tree.h"
//
// static const char* const
// ReadTextFromFile (const char* const file_name);
//
// static ANA_BinTree_node*
// GetNode (const char  * const tree_input,
//                size_t* const str_index,
//          const size_t        input_len);
//
// static ANA_BinTree_data_type
// GetData (const char* const tree_input, size_t* str_index,
//          ANA_BinTree_data_type data);
//
// ANA_BinTree*
// ReadTreeFromFile (ANA_BinTree* const tree,
//                   const char * const file_name)
// {
//     if (!tree)
//     {
//         fprintf (stderr, "Invalid pointer to tree struct: [%p]", tree);
//         return nullptr;
//     }
//
//     const char* const tree_input = ReadTextFromFile (file_name);
//     if (!tree_input)
//     {
//         return nullptr;
//     }
//
//     const size_t input_len = strlen (tree_input);
//
//     size_t str_index = 0;
//
//     GetNode (tree_input, &str_index, input_len, nullptr);
//
//
// }
//
// static ANA_BinTree_node*
// GetNode (const char  * const tree_input,
//                size_t* const str_index,
//          const size_t        input_len,
//          const ANA_BinTree_node* const parent)
// {
//     if (tree_input [*str_index] == '0')
//     {
//         return nullptr;
//     }
//
//     ANA_BinTree_data_type data = (ANA_BinTree_data_type)
//                                  calloc (sizeof (char), input_len);
//     ANA_BinTree_node* left  = nullptr;
//     ANA_BinTree_node* right = nullptr;
//
//     for (; *str_index < input_len; ++(*str_index))
//     {
//         if (tree_input [*str_index] == '(')
//         {
//             ++(*str_index);
//
//             GetData (tree_input, str_index, data);
//
//             left  = GetNode (tree_input, str_index, input_len, );
//             right = GetNode (tree_input, str_index, input_len);
//         }
//
//         if (tree_input [*str_index] == ')')
//         {
//             return ANA_BinTree_CtorNode (data, left, right, parent);
//         }
//     }
// }
//
// static ANA_BinTree_data_type
// GetData (const char* const tree_input, size_t* str_index,
//          ANA_BinTree_data_type data)
// {
//     if (tree_input [*str_index] == '\"')
//     {
//         size_t data_index = 0;
//         ++(*str_index);
//
//         while (tree_input [*str_index] != '\"')
//         {
//             data[data_index++] = tree_input[(*str_index)++];
//         }
//     }
//
//     return data;
// }
//
// static const char* const
// ReadTextFromFile (const char* const file_name)
// {
//     FILE* const fp = fopen (file_name, "rb");
//     if (!fp)
//     {
//         perror ("fopen() failed");
//         return nullptr;
//     }
//
//     fseek(fp, 0, SEEK_END);
//     size_t file_size = (size_t) ftell(fp);
//     fseek(fp, 0, SEEK_SET);
//
//     char* const tree_input = (char* const) calloc (file_size, sizeof (char));
//     fread (tree_input, sizeof (char), file_size, fp);
//
//     fclose (fp);
//
//     return tree_input;
// }
