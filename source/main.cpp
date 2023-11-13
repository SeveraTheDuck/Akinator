#include "../BinTree/include/ANA_BinTree_make_image.h"

int main (int /*argc*/, char** /*argv*/)
{
    ANA_BinTree tree = {};
    ANA_BinTree_Ctor (&tree, "Is it an animal?");

    tree.root->right = ANA_BinTree_CtorNode ("Lukashov", nullptr, nullptr, tree.root);
    tree.root->left  = ANA_BinTree_CtorNode ("Crocodile",  nullptr, nullptr, tree.root);

    ANA_BinTree_MakeTreeImage (&tree);

    return 0;
}
