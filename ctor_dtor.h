#ifndef CTOR_DTOR_H
#define CTOR_DTOR_H

int     ListCtor        (DLinkList_t* myLinkList);
int     ListDtor        (DLinkList_t* myLinkList);
int     MemPoison       (void* memptr, size_t num);
FILE*   OpenFileLog     (void);
int     CloseFile       (FILE *file_text);
size_t  SizeOfData      (DLinkList_t* myLinkList);
int     SetZeroElement  (DLinkList_t* myLinkList);
int     LinkFreeList    (Index_t IndexStart,DLinkList_t* myLinkList);

#endif