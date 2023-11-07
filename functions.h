#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int PushFirst (Elem_t InsertValue, DLinkList_t* myLinkList);

int InsertAfter (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList);
int InsertBefore (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList);

int PushBack (Elem_t InsertValue, DLinkList_t* myLinkList);
int PopBack (DLinkList_t* myLinkList);

int PushFront(Elem_t InsertValue, DLinkList_t* myLinkList);
int PopFront (DLinkList_t* myLinkList);

int Erase (Index_t EraseIndex, DLinkList_t* myLinkList);

int Resize (DLinkList_t* myLinkList);

#endif