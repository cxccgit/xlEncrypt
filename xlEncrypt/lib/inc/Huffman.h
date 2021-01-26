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

typedef struct _huffmanNode
{
    unsigned char * list;//被转换列表
    struct _huffmanNode * childTable;//子表 
}HuffmanNode;

typedef struct _huffmanTable
{
    HuffmanNode table[256];
}HuffmanTable;

#define getTreeNode(x) ((TreeNode*)x)

TreeNode * HFTBListToTree(unsigned int * tb);
void HFTBTreeToTable(TreeNode * root,HuffmanTable * ht);


#ifdef __cplusplus
}
#endif

#endif //!_HUFFMAN_H