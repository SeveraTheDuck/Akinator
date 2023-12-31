#ifndef READ_TREE_H
#define READ_TREE_H

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../BinTree/include/ANA_BinTree_struct.h"

const char* const TREE_INPUT_FILE_NAME = "tree_input.txt";

ANA_BinTree*
ReadTreeFromFile (ANA_BinTree* const tree,
                  const char * const file_name = TREE_INPUT_FILE_NAME);

ANA_BinTree_node*
ReadNode (ANA_BinTree*      const tree,
          ANA_BinTree_node* const parent,
          const char*       const input,
          size_t*           const input_shift);

#endif
