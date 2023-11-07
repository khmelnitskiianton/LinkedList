#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "functions.h"
#include "log.h"
#include "myassert.h"
#include "ctor_dtor.h"

int InsertAfter (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList)
{
    MYASSERT(myLinkList, BAD_POINTER_PASSED_IN_FUNC, return 0)
    MYASSERT((InsertIndex < myLinkList -> Capacity) && (*(myLinkList -> Next + InsertIndex) != 0) && (*(myLinkList -> Previous + InsertIndex) != -1), BAD_INDEX_IN_INSERTION, return 0)
    MYASSERT(myLinkList -> Free, DATA_IS_OVERFLOW, return 0)
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    Index_t IndexFree = myLinkList -> Free;
    Index_t IndexNext = *(myLinkList -> Next + InsertIndex);

    *(myLinkList -> Next + InsertIndex) = IndexFree;
    *(myLinkList -> Previous + IndexNext) = IndexFree;

    myLinkList -> Free = *(myLinkList -> Next + IndexFree);
    *(myLinkList -> Data + IndexFree) = InsertValue;
    *(myLinkList -> Previous + IndexFree) = InsertIndex;
    *(myLinkList -> Next + IndexFree) = IndexNext;
    
    PrintLogList (myLinkList, __PRETTY_FUNCTION__);

    return 1;
}

int InsertBefore (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList)
{
    MYASSERT(myLinkList, BAD_POINTER_PASSED_IN_FUNC, return 0)
    MYASSERT((InsertIndex < myLinkList -> Capacity) && (*(myLinkList -> Previous + InsertIndex) != 0) && (*(myLinkList -> Previous + InsertIndex) != -1), BAD_INDEX_IN_INSERTION, return 0)
    MYASSERT(myLinkList -> Free, DATA_IS_OVERFLOW, return 0)
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    Index_t IndexFree = myLinkList -> Free;
    Index_t IndexPrevious = *(myLinkList -> Previous + InsertIndex);

    *(myLinkList -> Previous + InsertIndex) = IndexFree;
    *(myLinkList -> Next + IndexPrevious) = IndexFree;

    myLinkList -> Free = *(myLinkList -> Next + IndexFree);
    *(myLinkList -> Data + IndexFree) = InsertValue;
    *(myLinkList -> Next + IndexFree) = InsertIndex;
    *(myLinkList -> Previous + IndexFree) = IndexPrevious; 

    PrintLogList (myLinkList, __PRETTY_FUNCTION__);

    return 1;
}

int PushBack (Elem_t InsertValue, DLinkList_t* myLinkList)
{
    MYASSERT(myLinkList, BAD_POINTER_PASSED_IN_FUNC, return 0)
    MYASSERT(myLinkList -> Free, DATA_IS_OVERFLOW, return 0)
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    if ((myLinkList -> Tail == 0) && (myLinkList -> Head == 0)) 
    {
        Index_t IndexFree = myLinkList -> Free;

        myLinkList -> Head = IndexFree;
        myLinkList -> Tail = IndexFree;
        myLinkList -> Free = *(myLinkList -> Next + IndexFree);
    
        *(myLinkList -> Data + IndexFree) = InsertValue;
        *(myLinkList -> Previous + IndexFree) = 0;
        *(myLinkList -> Next + IndexFree) = 0;

        PrintLogList (myLinkList, __PRETTY_FUNCTION__);

        return 1;
    }

    Index_t IndexFree = myLinkList -> Free;
    Index_t IndexTail = myLinkList -> Tail;

    *(myLinkList -> Next + IndexTail) = IndexFree;

    myLinkList -> Free = *(myLinkList -> Next + IndexFree);
    myLinkList -> Tail = IndexFree;

    *(myLinkList -> Data + IndexFree) = InsertValue;
    *(myLinkList -> Next + IndexFree) = 0;
    *(myLinkList -> Previous + IndexFree) = IndexTail;
    
    PrintLogList (myLinkList, __PRETTY_FUNCTION__);

    return 1;
}

int PopBack (DLinkList_t* myLinkList)
{
    MYASSERT(myLinkList, BAD_POINTER_PASSED_IN_FUNC, return 0)
    MYASSERT(myLinkList -> Tail, POP_BUT_DATA_IS_EMPTY, return 0)
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    Index_t IndexTail = myLinkList -> Tail;
    Index_t IndexPrevTail = *(myLinkList -> Previous + IndexTail); 
    myLinkList -> Tail = *(myLinkList -> Previous + IndexTail);

    *(myLinkList -> Data + IndexTail) = POISON_ELEMENT;
    *(myLinkList -> Next + IndexTail) = myLinkList -> Free;
    myLinkList -> Free = IndexTail;

    *(myLinkList -> Previous + IndexTail) = -1;
    *(myLinkList -> Next + IndexPrevTail) = 0; 

    PrintLogList (myLinkList, __PRETTY_FUNCTION__);    
    
    return 1;
}

int PushFront (Elem_t InsertValue, DLinkList_t* myLinkList)
{
    MYASSERT(myLinkList, BAD_POINTER_PASSED_IN_FUNC, return 0)
    MYASSERT(myLinkList -> Free, DATA_IS_OVERFLOW, return 0)
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    if ((myLinkList -> Tail == 0) && (myLinkList -> Head == 0)) 
    {
        Index_t IndexFree = myLinkList -> Free;

        myLinkList -> Head = IndexFree;
        myLinkList -> Tail = IndexFree;
        myLinkList -> Free = *(myLinkList -> Next + IndexFree);
    
        *(myLinkList -> Data + IndexFree) = InsertValue;
        *(myLinkList -> Previous + IndexFree) = 0;
        *(myLinkList -> Next + IndexFree) = 0;

        PrintLogList (myLinkList, __PRETTY_FUNCTION__);

        return 1;
    }

    Index_t IndexFree = myLinkList -> Free;
    Index_t IndexHead = myLinkList -> Head;

    *(myLinkList -> Previous + IndexHead) = IndexFree;

    myLinkList -> Free = *(myLinkList -> Next + IndexFree);
    myLinkList -> Head = IndexFree;

    *(myLinkList -> Data + IndexFree) = InsertValue;
    *(myLinkList -> Previous + IndexFree) = 0;
    *(myLinkList -> Next + IndexFree) = IndexHead;

    PrintLogList (myLinkList, __PRETTY_FUNCTION__);
    return 1;
}

int PopFront (DLinkList_t* myLinkList)
{
    MYASSERT(myLinkList, BAD_POINTER_PASSED_IN_FUNC, return 0)
    MYASSERT(myLinkList -> Head, POP_BUT_DATA_IS_EMPTY, return 0)
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    Index_t IndexHead = myLinkList -> Head;
    Index_t IndexNextHead = *(myLinkList -> Next + IndexHead); 
    myLinkList -> Head = *(myLinkList -> Next + IndexHead);

    *(myLinkList -> Data + IndexHead) = POISON_ELEMENT;
    *(myLinkList -> Next + IndexHead) = myLinkList -> Free;
    myLinkList -> Free = IndexHead;

    *(myLinkList -> Previous + IndexHead) = -1;
    *(myLinkList -> Previous + IndexNextHead) = 0; 

    PrintLogList (myLinkList, __PRETTY_FUNCTION__);    
    
    return 1;
}

int Erase (Index_t EraseIndex, DLinkList_t* myLinkList)
{
    MYASSERT(myLinkList, BAD_POINTER_PASSED_IN_FUNC, return 0)
    MYASSERT((*(myLinkList -> Previous + EraseIndex) != -1) && (EraseIndex > 0) && (EraseIndex < myLinkList -> Capacity), BAD_INDEX_TO_ERASE, return 0)
    MYASSERT(((myLinkList -> Previous + EraseIndex) != 0) && ((myLinkList -> Next + EraseIndex) != 0),ERASE_HEAD_OR_TAIL,return 0)
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    Index_t IndexNext = *(myLinkList -> Next + EraseIndex);
    Index_t IndexPrevious = *(myLinkList -> Previous + EraseIndex);
    *(myLinkList -> Next + IndexPrevious) = IndexNext;
    *(myLinkList -> Previous + IndexNext) = IndexPrevious;

    *(myLinkList -> Data + EraseIndex) = POISON_ELEMENT;
    *(myLinkList -> Next + EraseIndex) = myLinkList -> Free;
    *(myLinkList -> Previous + EraseIndex) = -1;
    myLinkList -> Free = EraseIndex;

    PrintLogList (myLinkList, __PRETTY_FUNCTION__);

    return 1;
}

int Resize (DLinkList_t* myLinkList)
{
    MYASSERT(!(myLinkList -> Free), DATA_IS_NOT_FULL, return 0)    
    MYASSERT((myLinkList -> Tail < myLinkList -> Capacity) && (myLinkList -> Head < myLinkList -> Capacity), TAIL_OR_HEAD_OUT_OF_CAPACITY, return 0)

    Index_t OldCapacity = myLinkList -> Capacity;
    (myLinkList -> Capacity) = (myLinkList -> Capacity) * MULTIPLIER;

    MYASSERT(myLinkList -> Data = (Elem_t*) realloc (myLinkList -> Data, SizeOfData (myLinkList)), BAD_REALLOC_DATA, return 0)
    MemPoison((char*) myLinkList -> Data + sizeof(Elem_t)*((size_t) OldCapacity), (size_t) (myLinkList -> Capacity - OldCapacity));

    MYASSERT(myLinkList -> Next = (Index_t*) realloc (myLinkList -> Next, SizeOfData (myLinkList)), BAD_REALLOC_NEXT, return 0)
    MYASSERT(myLinkList -> Previous = (Index_t*) realloc (myLinkList -> Previous, SizeOfData (myLinkList)), BAD_REALLOC_PREV, return 0)
    
    myLinkList -> Free = OldCapacity;
    LinkFreeList(OldCapacity, myLinkList);

    PrintLogList (myLinkList, __PRETTY_FUNCTION__);  
    return 1;
}