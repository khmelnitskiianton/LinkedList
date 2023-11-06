#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "main.h"
#include "ctor_dtor.h"

int ListCtor (DLinkList_t* myLinkList)
{
    myLinkList -> Capacity  = INITIAL_SIZE;
    myLinkList -> FileLog   = OpenFileLog ();
    myLinkList -> NumImage  = 1;

    assert(myLinkList -> Data     = (Elem_t*)  calloc (1, SizeOfData (myLinkList)));
    assert(myLinkList -> Next     = (Index_t*) calloc ((size_t) myLinkList -> Capacity, sizeof(Index_t)));
    assert(myLinkList -> Previous = (Index_t*) calloc ((size_t) myLinkList -> Capacity, sizeof(Index_t)));

    MemPoison ((char*) myLinkList -> Data, INITIAL_SIZE);


    SetZeroElement(myLinkList);
    myLinkList -> Head = 0;
    myLinkList -> Tail = 0;
    myLinkList -> Free = 1;


    LinkFreeList(1, myLinkList);

    //TODO: check errors
    return 1;
}

int ListDtor (DLinkList_t* myLinkList)
{
    CloseFile (myLinkList -> FileLog);
    free (myLinkList -> Data);
    free (myLinkList -> Next);
    free (myLinkList -> Previous);
    return 1;

    //TODO: free() check;
}

int MemPoison (void* memptr, size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        *(((Elem_t*) memptr) + i) = POISON_ELEMENT;
    }
    return 1;
}

FILE* OpenFileLog (void)
{
    FILE *file_write = fopen (FILE_LOG, "w");

    assert(file_write);

    return file_write;
}

int CloseFile (FILE *file_text)
{
	assert(file_text);
	assert(!fclose (file_text));
	
    return 1;
}

size_t SizeOfData (DLinkList_t* myLinkList)
{
    return sizeof(Elem_t)*((size_t) (myLinkList -> Capacity));
}

int SetZeroElement (DLinkList_t* myLinkList)
{
    *(myLinkList -> Next) = 0;
    *(myLinkList -> Previous) = 0;
    return 1;
}

int LinkFreeList (Index_t IndexStart,DLinkList_t* myLinkList)
{
    for (int i = IndexStart; i < (myLinkList -> Capacity); i++)
    {
        if (i == ((myLinkList -> Capacity) - 1)) *((myLinkList -> Next) + i) = 0;
        else                                     *((myLinkList -> Next) + i) = i + 1;
        *((myLinkList -> Previous) + i) = -1;
    }
    return 1;
}