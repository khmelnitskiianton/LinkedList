# LinkedList
Realization of double linked list made on indexes

Functions:

1. Constructor and destructor of list.
```cpp
int     ListCtor        (DLinkList_t* myLinkList);
int     ListDtor        (DLinkList_t* myLinkList);
```
2. Insertion by index, insertion in head/tail, pop head/tail, erase by index.
```cpp
int InsertAfter (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList);
int InsertBefore (Index_t InsertIndex, Elem_t InsertValue, DLinkList_t* myLinkList);

int PushBack (Elem_t InsertValue, DLinkList_t* myLinkList);
int PopBack (DLinkList_t* myLinkList);

int PushFront(Elem_t InsertValue, DLinkList_t* myLinkList);
int PopFront (DLinkList_t* myLinkList);

int Erase (Index_t EraseIndex, DLinkList_t* myLinkList);
```
