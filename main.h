#ifndef MAIN_H
#define MAIN_H

#include <limits.h>

typedef int Elem_t;
typedef int Index_t;
#define SPECIFIER "%d"

const int    INITIAL_SIZE   = 10;
const Elem_t POISON_ELEMENT = 666;
const int    N_ERRORS       = 16;
const int    MULTIPLIER     = 2;

typedef struct DLinkList {
    Elem_t*     Data;
    Index_t*    Next;
    Index_t*    Previous;

    Index_t     Capacity;
    Index_t     Head;
    Index_t     Tail;
    Index_t     Free;
    
    size_t      NumImage;
    FILE*       FileLog;
    FILE*       FileGraph;
} DLinkList_t;

#define FILE_LOG "log.html"
#define FILE_GRAPH "list.dot"
#define PLACE_IMAGE "./images/"
#define TYPE_OF_IMAGE "png"
#define SIZE_OF_COMMAND 500
#define FILL_BACK_COLOR "#ff7f50"
#define FILL_BACK_LIST "#ffe4c4"
#define COLOR_EDGE "#800000"

#define ASSERT_MYLIST 1
#define DEBUG_PRINTING 1

#if (DEBUG_PRINTING != 0)
#define ON_PRINTING(...) __VA_ARGS__
#else
#define ON_PRINTING(...) 
#endif

#endif