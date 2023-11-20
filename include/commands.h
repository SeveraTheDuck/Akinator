#ifndef AKINATOR_COMMANDS_H
#define AKINATOR_COMMANDS_H

#include "../stack/headers/stack.h"
#include "../BinTree/include/ANA_BinTree_struct.h"
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

const size_t OBJECT_NAME_MAX_LEN    = 50;
const size_t NEW_DIFFERENCE_MAX_LEN = 200;

enum AnswerIndicator
{
    NODE_ANSWER_NO  = 0,
    NODE_ANSWER_YES = 1
};

ANA_BinTree_node*
GuessObject (ANA_BinTree* const tree);

ANA_BinTree_node*
GetNewNode (ANA_BinTree*      const tree,
            ANA_BinTree_node* const cur_node);

void
DescribeObject (const ANA_BinTree* const tree,
                const char*        const object);

ANA_BinTree_node*
FindObject (      ANA_BinTree_node* const node,
            const char*             const object);

#endif
