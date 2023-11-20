#ifndef ANA_BINTREE_CONFIG_H
#define ANA_BINTREE_CONFIG_H

typedef char* ANA_BinTree_data_type;
#define ANA_BinTree_OUTPUT_F "%s"

const ANA_BinTree_data_type ANA_BinTree_POISON = nullptr;

const char* const ANA_BinTree_IMAGE_CONSTRUCT_FILE_NAME = "image_construct.dot";
const char* const ANA_BinTree_IMAGE_FILE_NAME = "tree.png";

const size_t MAX_NUM_OF_ALLOCATED_DATA = 50;

const size_t DESCRIPTION_MAX_LEN = 200;

#endif
