#ifndef MYASSERT_H
#define MYASSERT_H

#include <assert.h>

#include "colors.h"

#define DEBUG 1

enum CODES_OF_ERRORS {
    BAD_POINTER_PASSED_IN_FUNC   = 1,
    POP_BUT_DATA_IS_EMPTY        = 2,
    DATA_IS_OVERFLOW             = 3,
    BAD_INDEX_IN_INSERTION       = 4,
    BAD_INDEX_TO_ERASE           = 5,  
    ERASE_HEAD_OR_TAIL           = 6,
    DATA_IS_NOT_FULL             = 7,   
    BAD_REALLOC_DATA             = 8,
    BAD_REALLOC_NEXT             = 9,
    BAD_REALLOC_PREV             = 10,
    TAIL_OR_HEAD_OUT_OF_CAPACITY = 11,
};

#ifdef DEBUG
#define MYASSERT(check, error_code, ending)                                                                         \
        do                                                                                                          \
        {                                                                                                           \
            if (!(check))                                                                                           \
            {                                                                                                       \
                printf(MAGENTA ">>>>> Error in code! Error code: %s <<<<<\n", #error_code);                         \
                printf("In File: %s, In Line: %d, In Function: %s\n", __FILE__, __LINE__,__PRETTY_FUNCTION__);      \
                printf("In this condition:\t\"%s\"\n\n" RESET, #check);                                             \
                ending;                                                                                             \
            }                                                                                                       \
        }                                                                                                           \
        while(0);
#else   
#define MYASSERT(check, error_code, ending)
#endif

#endif