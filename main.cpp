#include <stdio.h>

#include "main.h"
#include "ctor_dtor.h"
#include "log.h"

int main()
{
    DLinkList_t myLinkList = {};

    ListCtor (&myLinkList);
    PrintLogStart (&myLinkList);

    PrintLogList (&myLinkList);
    PrintLogList (&myLinkList);

    PrintLogFinish (&myLinkList);
    ListDtor (&myLinkList);

    printf("!!!!!!!!!!!!!!! <GOOD ENDING. CHECK log.html> !!!!!!!!!!!\n");
    return 0;
}