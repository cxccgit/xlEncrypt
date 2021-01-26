#ifndef _LIST_H
#define _LIST_H

#include<stdio.h>

#define ERROR -1
#define OK 0

#define myFree free
#define myMalloc malloc

#define FIND_PDATA 1
#define FIND_VALUE 2

typedef struct  _listnode
{
    unsigned int value;
    void * pdata;
    struct _listnode* next;
}ListNode;

typedef struct _list
{
    ListNode * head;
    ListNode * tail;
    unsigned int length;
}List;

//初始化list
#define initList(x) (x)->head=NULL;(x)->tail=NULL;(x)->length=0;

//按顺序插入(value从小到大)
int insertSort(List* list, ListNode* p);
//插入到列表尾部
int insertTail(List* list, ListNode* p);
//释放列表
int freeList(List* list);

ListNode* getPdata(List* list, void* ptr, int mode);

void* remove1(List* list, ListNode* p1);

void showList(List* list);


#endif //!_LIST_H
