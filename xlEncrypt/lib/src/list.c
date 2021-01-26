#include"../inc/list.h"

int insertTail(List * list,ListNode * p)
{
    if (list->head == NULL) {
        list->head = p;
        p->next = p;
        list->tail = p;
        list->length++;
        return OK;
    }
    p->next = list->tail->next;
    list->tail->next = p;
    /*if(list->head==NULL){
        list->head = list->tail;
        p->next = list->head;
    }
    else{

    }*/
    list->length++;
    return OK;
}

int insertSort(List * list,ListNode * p)
{
    ListNode * ptr = list->head;
    if (list->head == NULL) {
        list->head = p;
        p->next = p;
        list->tail = p;
        list->length++;
        return OK;
    }
    if(p->value<list->head->value){
        p->next = list->head;
        list->head = p;
        list->tail->next = list->head;
        list->length++;
        return OK;
    }
    while(ptr->next!=list->head){
        if(p->value<ptr->next->value){
            p->next = ptr->next;
            ptr->next = p;
            list->length++;
            return OK;
        }
        ptr = ptr->next;
    }
    if(ptr->next == list->head){
        p->next=list->head;
        list->tail->next = p;
        list->tail = p;
        list->length++;
        return OK;
    }
    return ERROR;
}
int swapData(ListNode* p1, ListNode* p2)
{
    unsigned int buf = 0;
    buf = p1->value;
    p1->value = p2->value;
    p2->value = buf;
    buf = (unsigned int)p1->pdata;
    p1->pdata = p2->pdata;
    p2->pdata = (void*)buf;
    return 0;
}
void * remove1(List * list,ListNode* p1)
{
    ListNode* p2 = p1->next;
    unsigned int buf = 0;
    if (p1 == list->tail) {
        return NULL;
    }
    buf = p1->value;
    p1->value = p2->value;
    p2->value = buf;
    buf = (unsigned int)p1->pdata;
    p1->pdata = p2->pdata;
    p2->pdata = (void*)buf;
    buf = (unsigned int)p1->next;
    p1->next = p2->next;
    p2->next = (ListNode*)buf;
    if (p2 == list->tail) {
        list->tail = p1;
    }
    return p2;
}
int freeList(List * list)
{
    ListNode * p = list->head;
    if (p == NULL)
        return OK;
    if (list->tail->next == NULL)
        return ERROR;
    list->tail->next = NULL;
    while(p!=NULL){
        list->head = p->next;
        myFree(p);
        p=list->head;
    }
    return OK;
}
//查找
ListNode * getPdata(List * list,void * ptr,int mode)
{
    ListNode * p = list->head;
    if(mode == FIND_PDATA){
        if(p->pdata == ptr){
            return list->head;
        }
        else{
            p=p->next;
        }
        while(p!=list->head){
            if(p->pdata == ptr){
                return p;
            }
        }
    }
    else{
        if(p->value == (unsigned int)ptr){
            return list->head;
        }
        else{
            p=p->next;
        }
        while(p!=list->head){
            if(p->value == (unsigned int)ptr){
                return p;
            }
        }
    }
    return NULL;
}

void showList(List * list)
{
    ListNode* p = list->head;
    if (p == NULL)
        return;
    printf("\n%d\t",p->value);
    p = p->next;
    while (p != NULL&&p!=list->head) {
        printf("%d\t", p->value);
        p = p->next;
    }
    printf("\n");
}
/*int remove(ListNode * listnode)
{
    ListNode * p1 = NULL;
    listnode->pdata = listnode->next->pdata;
    //((TaskStruct*)p->pdata)->listnode = p;
    listnode->value = listnode->next->value;
    p1 = listnode->next;
    listnode->next  = listnode->next->next;
    myFree(p1);
    return 0;
}*/
