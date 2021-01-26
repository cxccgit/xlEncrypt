#include"../inc/Huffman.h"

void HFTBTreeToDeTable(TreeNode * root,HuffmanTable * ht)
{
    unsigned char buf[8];
    unsigned char f=0,num,n,bit;
    TreeNode * p = root;
    int i,j;
    for(i = 0;i<256;i++)
    {
        num = i;
        f = 0x08;
        n = 0;
        bit=0;
        for(j=0;j<8;j++)
        {
            if(p->left==NULL||p->right==NULL)
            {
                buf[n++] = p->data;
                bit=i;
                p = root;
            }
            if(num&f)
                p=p->right;
            else
                p=p->left;
        }
        
        if(n==0)
        {
            ht->table[i].childTable = p;
        }
        else
        {
            ht->table->list = (unsigned char*)malloc(n+2);
            ht->table->list[0] = n;
            ht->table->list[1] = bit+1;
            for(j=2;2<n+2;j++)
                ht->table->list[j] = buf[j-2];
        }
        p = root;
    }
}

TreeNode * HFTBListToTree(unsigned int * tb)
{
    List list;
    ListNode * p = NULL;
    TreeNode * tnp = NULL;
    initList(&list);
    for(int i=0;i<256;i++)
    {
        p = (ListNode*)malloc(sizeof(ListNode));
        p->value = tb[i];
        p->pdata = malloc(sizeof(TreeNode));
        getTreeNode(p->pdata)->data = i;
        getTreeNode(p->pdata)->w = tb[i];
        getTreeNode(p->pdata)->left = NULL;
        getTreeNode(p->pdata)->right = NULL;
        insertSort(&list,p);
    }
    while(list.length>1)
    {
        tnp = (TreeNode*)malloc(sizeof(TreeNode));
        tnp->data = 0;
        tnp->left = list.head->pdata;
        tnp->right = list.head->next->pdata;
        tnp->w = tnp->left->w+tnp->right->w;

        p = list.head;list.head = list.head->next;free(p);
        p = list.head;list.head = list.head->next;free(p);
        list.length-=2;

        p = (ListNode*)malloc(sizeof(ListNode));
        p->value = tnp->w;
        p->pdata = tnp;
        insertSort(&list,p);
    }
    return tnp;
}