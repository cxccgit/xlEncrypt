#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include<stdio.h>
#include<stdlib.h>
#include"list.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _treeNode
{
    unsigned char data;
    unsigned int w;
    struct _treeNode * left;
    struct _treeNode * right;
}TreeNode;

typedef struct _huffmanDeNode
{
    unsigned char * list;//被转换列表
    TreeNode * childTable;//子表 
}HuffmanDeNode;

typedef struct _huffmanEnNode
{
    unsigned char data;
    unsigned char size;
}HuffmanEnNode;

#define getTreeNode(x) ((TreeNode*)x)

TreeNode * HFTBListToTree(unsigned int * tb);
void HFTBTreeToDeTable(TreeNode * root, HuffmanDeNode* ht);
void HFTBTreeToEnTable(TreeNode* root, HuffmanEnNode* ht);




#ifdef __cplusplus
}
#endif

#endif //!_HUFFMAN_H