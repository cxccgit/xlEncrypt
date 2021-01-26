#include"main.h"

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"lib/inc/Huffman.h"
#pragma warning(disable:4996)

//#define TEST

#ifdef TEST

//#define TESTHuffmanTree 
#define TESTFILE

#endif

#ifdef TESTHuffmanTree
#define N(x,y,z)  buf[x].data = 0;buf[x].w = x;buf[x].left = &buf[y];buf[x].right=&buf[z]
#define NCX(x,y) buf[x].data = y;buf[x].w = x;buf[x].left = NULL;buf[x].right=NULL;
#endif
int main()
{

	
	unsigned int fe[256];
	size_t size;
	unsigned char buffer[256];
#ifdef TESTFILE
	srand((unsigned int)time(NULL));
	FILE* fptest = fopen("test.b", "w");
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < 256; i++)
		{
			buffer[i] = rand() % 256;
		}
		fwrite(buffer, 1, 256, fptest);
	}
	fclose(fptest);
#endif
#ifndef TEST
	/*FILE* fp = fopen("test.b","rb");
	for (int i = 0; i < 256; fe[i++] = 0);
	do
	{
		size = fread(buffer,1,256,fp);
		for (int i = 0; i < size; i++)
			fe[buffer[i]]++;

	} while (size == 256);
	fclose(fp);
	TreeNode * p = HFTBListToTree(fe);
	HuffmanEnNode hp[256];
	HFTBTreeToEnTable(p, hp);*/
	encodeing("main.exe","test.out");

#endif
#ifdef TESTHuffmanTree
	TreeNode buf[12];
	N(1,2,3);
	N(2,4,11);
	N(4,5,6);
	NCX(5,1);
	N(6,7,8);
	NCX(7,2);
	N(8,9,10);
	NCX(9,3);
	NCX(10,4);
	NCX(11,5);
	NCX(3,6);
	HuffmanEnNode hp[7];
	HFTBTreeToEnTable(&buf[1], &hp);
#endif
	return 0;
}
