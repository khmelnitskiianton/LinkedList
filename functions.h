#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int InsertAfter (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList, const char* function);
int InsertBefore (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList, const char* function);

int PushBack (Elem_t InsertValue, DLinkList_t* myLinkList, const char* function);
int PopBack (DLinkList_t* myLinkList, const char* function);

int PushFront(Elem_t InsertValue, DLinkList_t* myLinkList, const char* function);
int PopFront (DLinkList_t* myLinkList, const char* function);

int Erase (Index_t EraseIndex, DLinkList_t* myLinkList, const char* function);

int Resize (DLinkList_t* myLinkList, const char* function);

// int EnterValue (DLinkList_t* myLinkList, const char* function);
// int StopEnter (void);
// int clean_buffer (void);

#endif