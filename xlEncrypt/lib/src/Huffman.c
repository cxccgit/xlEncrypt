#include"../inc/Huffman.h"
#pragma warning(disable:4996)

//频率表到哈夫曼树，返回根节点
TreeNode* HFTBListToTree(unsigned int* tb)
{
    TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* ret = p;
    TreeNode* moveP = NULL;
    p->data = 0x00;
    p->left = NULL;
    p->right = NULL;
    p->w = 0;
    if (tb[0] == 0)
        tb[0]++;
    //排序
    for (int i = 0; i < 256; i++) {
        p = (TreeNode*)malloc(sizeof(TreeNode));
        p->data = i;
        p->left = NULL;
        p->right = NULL;
        p->w = tb[i];

        for (moveP = ret; moveP->right != NULL && moveP->right->w <= p->w; moveP = moveP->right);

        if (moveP->right == NULL)
            moveP->right = p;
        else {
            p->right = moveP->right;
            moveP->right = p;
        }
    }
    //在每个节点下下挂一个值相同的节点作为该值的叶子节点
    for (moveP = ret; moveP != NULL; moveP = moveP->right)
    {
        moveP->left = (TreeNode*)malloc(sizeof(TreeNode));
        moveP->left->data = moveP->data;
        moveP->left->left = NULL;
        moveP->left->right = NULL;
        moveP->left->w = moveP->w;
        moveP->data = 0xFF;
    }
    while (1)
    {
        //权值求和
        p = ret;
        ret = ret->right;
        p->w += p->right->w;
        p->right->w = p->w;
        //移动节点
        moveP = p->right->left;
        p->right->left = p;
        p->right = moveP;
        //准备插入
        p = ret;
        ret = ret->right;
        //结束判断
        if (ret == NULL)
            break;
        if (p->w <= ret->w)
        {
            p->left = ret;
            ret = p;
        }
        else {
            for (moveP = ret; moveP->left != NULL && moveP->left->w < p->w; moveP = moveP->left);
            if (moveP->left == NULL)
                moveP->left = p;
            else {
                p->left = moveP->left;
                moveP->left = p;
            }
        }
    }
    ret = p->left;
    free(p);
    return ret;
}
//哈夫曼树到编码表
void HFTBTreeToEnTable(TreeNode* root, HuffmanEnNode * ht)
{
    TreeNode* stack[20];
    int deep[20];
    int stackP = -1;
    TreeNode* p = root;
    unsigned int  data = 0;
    unsigned char size = 0;
    do
    {
        //判断是否为叶子节点   
        if (p->left == NULL && p->right == NULL)
        {
            ht[p->data].data = data;
            ht[p->data].size = size;
            data <<= 1;
            size++;
            do
            {
                if (stackP == -1)
                    goto End;
                data >>= size - deep[stackP];
                size = deep[stackP];
                p = stack[stackP--];
            }while (p == NULL);
            data |= 0x01;
            continue;
        }
        stackP++;
        stack[stackP] = p->right;
        deep[stackP] = size+1;
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

void encodeing(char * file,char * file1)
{
    size_t size;
    unsigned int fe[256];
    unsigned char buffer[256];
    for (int i = 0; i < 256; fe[i++] = 0);
    FILE* fp = fopen(file, "rb");
    do
    {
        size = fread(buffer, 1, 256, fp);
        for (int i = 0; i < size; i++)
            fe[buffer[i]]++;

    } while (size == 256);
    fclose(fp);
    //频率表转为哈夫曼树
    TreeNode* p = HFTBListToTree(fe);
    HuffmanEnNode hp[256];
    //哈夫曼树转哈夫曼编码表
    HFTBTreeToEnTable(p, hp);
    FILE* fpOut = fopen(file1, "wb");
    //写霍夫曼表
    fwrite(fe, sizeof(unsigned int), 256, fpOut);
    fp = fopen(file, "rb");
    int j = 0;
    unsigned char bitnum = 0;
    unsigned int b = 0;
    unsigned char* bP = &b;
    unsigned char outBuf[256];
    do
    {
        size = fread(buffer, 1, 256, fp);
        for (int i = 0; i < size; i++)
        {
            b <<= hp[buffer[i]].size;
            b |= hp[buffer[i]].data;
            bitnum += hp[buffer[i]].size;
            if (i == 255)
                i = i;
            if(bitnum >= 8) {
                b <<= 8-bitnum%8;
                do {
                    bitnum -= 8;
                    outBuf[j++] = bP[bitnum / 8 + 1];
                } while (bitnum >= 8);
                b >>= 8 - bitnum;
            }
        }
        fwrite(fe, sizeof(unsigned char), j, fpOut);
        j = 0;
    } while (size == 256);

    fclose(fp);
    fclose(fpOut);
}
