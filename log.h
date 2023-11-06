#ifndef LOG_H
#define LOG_H

int     PrintLogStart   (DLinkList_t* myLinkList);
int     PrintLogFinish  (DLinkList_t* myLinkList);
int     PrintLogList    (DLinkList_t* myLinkList, const char* function);
int     GenerateImage   (DLinkList_t* myLinkList);
int     GenerateGraph   (DLinkList_t* myLinkList, const char* function);
FILE*   OpenFileGraph   (void);
int     WriteVarsToGraph(DLinkList_t* myLinkList);
int     WriteListToGraph(DLinkList_t* myLinkList);

#endif