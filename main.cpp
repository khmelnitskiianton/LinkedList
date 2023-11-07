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

    PushFirst(100, &myLinkList);
    PushBack(51, &myLinkList);
    PushFront(20, &myLinkList);
    PushBack(33, &myLinkList);
    PushFront(77, &myLinkList);
    PushBack(58, &myLinkList);

    InsertAfter(2, 8, &myLinkList);

    InsertBefore(4, 9, &myLinkList);
    
    PushBack(48, &myLinkList);

    Resize(&myLinkList);

    PushBack(58, &myLinkList);
    PushBack(10, &myLinkList);

    PrintLogFinish (&myLinkList);
    ListDtor (&myLinkList);

    printf("\n!!!!!!!!!!!!!!! <GOOD ENDING. CHECK LOG.HTML> !!!!!!!!!!!\n");
    return 0;
}