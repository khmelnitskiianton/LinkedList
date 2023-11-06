#include <stdio.h>
#include <ctype.h>

#include "main.h"
#include "ctor_dtor.h"
#include "log.h"
#include "functions.h"
#include "myassert.h"
#include "ctor_dtor.h"

int main()
{
    DLinkList_t myLinkList = {};

    ListCtor (&myLinkList);
    PrintLogStart (&myLinkList);

    PrintLogList (&myLinkList, __PRETTY_FUNCTION__);

    PushBack(51, &myLinkList, __PRETTY_FUNCTION__);
    PushBack(20, &myLinkList, __PRETTY_FUNCTION__);
    PushBack(33, &myLinkList, __PRETTY_FUNCTION__);
    PushBack(77, &myLinkList, __PRETTY_FUNCTION__);
    PushBack(58, &myLinkList, __PRETTY_FUNCTION__);
    PushBack(29, &myLinkList, __PRETTY_FUNCTION__);

    InsertAfter(2, 8, &myLinkList, __PRETTY_FUNCTION__);

    InsertBefore(5, 9, &myLinkList, __PRETTY_FUNCTION__);
    
    PushBack(48, &myLinkList, __PRETTY_FUNCTION__);

    Resize(&myLinkList, __PRETTY_FUNCTION__);

    PushBack(58, &myLinkList, __PRETTY_FUNCTION__);
    PushBack(10, &myLinkList, __PRETTY_FUNCTION__);

    PrintLogFinish (&myLinkList);
    ListDtor (&myLinkList);

    printf("\n!!!!!!!!!!!!!!! <GOOD ENDING. CHECK LOG.HTML> !!!!!!!!!!!\n");
    return 0;
}