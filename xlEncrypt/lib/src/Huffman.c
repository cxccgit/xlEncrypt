#include"../inc/Huffman.h"
void HFTBTreeToEnTable(TreeNode* root, HuffmanEnNode * ht)
{
    TreeNode* stack[20];
    int stackP = -1;
    TreeNode* p = root;
    unsigned char data = 0;
    unsigned char size = 0;
    do
    {
        //压栈右子树
        stack[++stackP] = p->right;
        if (p->left == NULL && p->right == NULL)
        {
            ht[p->data].data = data;
            ht[p->data].size = size;
            stackP--;//出栈空的右子树
            p = stack[stackP--];
            while (p == NULL)
            {
                p = stack[stackP--];
                if (stackP == -1)
                    goto End;
            }
            data = data >> (size - (stackP + 1));
            data |= 0x01;
            size = stackP + 1;
            stack[++stackP] = p->right;
        }
        data = data << 1;
        size++;
        p = p->left;
    } while (1);
End:
    return;
}

//哈夫曼树到解码表
void HFTBTreeToDeTable(TreeNode * root, HuffmanDeNode* ht)
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
                bit=j;
                p = root;
            }
            if(num&f)
                p=p->right;
            else
                p=p->left;
        }
        
        if(n==0)
        {
            ht[i].childTable = p;
        }
        else
        {
            ht[i].list = (unsigned char*)malloc(n+2);
            ht[i].list[0] = n;
            ht[i].list[1] = bit+1;
            ht[i].childTable = NULL;
            for(j=2;j<n+2;j++)
                ht[i].list[j] = buf[j-2];
        }
        p = root;
    }
}
//频率表到哈夫曼树，返回根节点
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
        p->next = NULL;
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