#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "main.h"
#include "log.h"
#include "ctor_dtor.h"

int PrintLogStart (DLinkList_t* myLinkList)
{
    system("rm images/*");
    fprintf(myLinkList -> FileLog,  "<!DOCTYPE html>\n"
                                    "<html lang=\"eng\">\n"
                                    "<head>\n"
                                    "<meta charset = \"utf-8\"/>\n"
                                    "<title>LOGS</title>\n"
                                    "<style>\n"
                                    "body {\n"
                                    "\tbackground-color: " FILL_BACK_COLOR ";\n"
                                    "}\n"
                                    "</style>\n"
                                    "</head>\n");
                                        
    fprintf(myLinkList -> FileLog,  "<body>\n"
                                    "<pre>\n"
                                    "<header>\n"
                                    "<h1> Logs for double-linked list </h1>\n"
                                    "</header>\n"
                                    "<main>\n"
                                    "<pre>\n"); 
    return 1;
}

int PrintLogFinish (DLinkList_t* myLinkList)
{
    fprintf(myLinkList -> FileLog,  "</pre>\n"
                                    "</main>\n"
                                    "</body>\n"
                                    "</html>\n"); 
    return 1;
}

int PrintLogList (DLinkList_t* myLinkList, const char* function)
{
    fprintf(myLinkList -> FileLog, "\n");

    GenerateGraph (myLinkList, function);
    GenerateImage (myLinkList);
    fprintf(myLinkList -> FileLog, "<img src=\"images/%lu.png\" alt=\"Распечатка списка %lu\">\n", myLinkList -> NumImage, myLinkList -> NumImage);
    (myLinkList -> NumImage)++;

    return 1;
}

int GenerateGraph (DLinkList_t* myLinkList, const char* function)
{
    myLinkList -> FileGraph = OpenFileGraph();

    fprintf (myLinkList -> FileGraph,   "digraph G{\n"
                                        "rankdir = LR;\n"
                                        "bgcolor = \"" FILL_BACK_COLOR "\";\n"
                                        "node[color = \"" COLOR_EDGE "\", fontsize = 10];\n"
                                        "edge[color = \"" COLOR_EDGE "\", fontsize = 15];\n"
                                        );

    fprintf(myLinkList -> FileGraph,    "subgraph cluster_list {\n"
                                        "\tnode[style = filled, color = white, fontsize = 10];\n"
                                        "\tedge[color = \"" COLOR_EDGE "\", fontsize = 15];\n"
                                        "\tstyle = \"dashed\";\n"
                                        "\tcolor = \"" "#800080" "\";\n"
                                        );

    WriteListToGraph(myLinkList);

    fprintf (myLinkList -> FileGraph,   "\tlabel = \"DOUBLE-LINKED LIST called from %s \";\n"
                                        "}\n"
                                        "All[shape = Mrecord, label = \" HEADER | <f0> Capacity: %d | <f1> Head: %d | <f2> Tail: %d | <f3> Free: %d \", style = \"filled\", fillcolor = \"" FILL_BACK_LIST "\"];\n"
                                        ,function, myLinkList -> Capacity, myLinkList -> Head, myLinkList -> Tail, myLinkList -> Free
                                        );

    WriteVarsToGraph(myLinkList);
                                        
    fprintf (myLinkList -> FileGraph,   "}\n");

    CloseFile (myLinkList -> FileGraph);
    return 1;
} 

int GenerateImage (DLinkList_t* myLinkList)
{
    char Command[SIZE_OF_COMMAND] = {};
    snprintf(Command, SIZE_OF_COMMAND,"dot " FILE_GRAPH " -T " TYPE_OF_IMAGE " -o " PLACE_IMAGE "%lu.png", myLinkList -> NumImage);
    system (Command);
    return 1;
}

FILE* OpenFileGraph (void)
{
    FILE *file_write = fopen (FILE_GRAPH, "w");

    assert(file_write);

    return file_write;
}

int WriteListToGraph(DLinkList_t* myLinkList)
{
    for (int i = 0; i < myLinkList -> Capacity; i++)
    {
        fprintf (myLinkList -> FileGraph, "\t%d [shape = Mrecord, style = filled, fillcolor = \"" FILL_BACK_LIST "\", color = \"#800000\", label = \" IP: %d | DATA: " SPECIFIER " | NXT: %d | PRV: %d \"];\n", i, i, *(myLinkList -> Data + i), *(myLinkList -> Next + i), *(myLinkList -> Previous + i));
    }

    fprintf (myLinkList -> FileGraph, "\n\t");
    for (int i = 0; i < (myLinkList -> Capacity - 1); i++)
    {
        fprintf (myLinkList -> FileGraph, "%d -> ", i);
    }
    fprintf (myLinkList -> FileGraph, "%d [weight = 10000, color = \"" FILL_BACK_COLOR "\"];\n\n", (myLinkList -> Capacity - 1));

    for (int i = 0; i < (myLinkList -> Capacity); i++)
    {
        if ((*(myLinkList -> Previous + i) == -1) && (*(myLinkList -> Next + i) != 0)) fprintf (myLinkList -> FileGraph, "\t%d -> %d [color = \"#00ff00\", weight = 0]\n", i, *(myLinkList -> Next + i));
        else if (*(myLinkList -> Next + i) != 0) fprintf (myLinkList -> FileGraph, "\t%d -> %d [color = \"#0000ff\", weight = 0]\n", i, *(myLinkList -> Next + i));
    }

    for (int i = 0; i < (myLinkList -> Capacity); i++)
    {
        if ((*(myLinkList -> Previous + i) != -1) && (*(myLinkList -> Previous + i) != 0)) fprintf (myLinkList -> FileGraph, "\t%d -> %d [color = \"#ff0000\", weight = 0]\n", i, *(myLinkList -> Previous + i));
    }

    return 1;
}

int WriteVarsToGraph(DLinkList_t* myLinkList)
{
    fprintf(myLinkList -> FileGraph, "All:<f1> -> %d [color = \"#FFFFFF\"];\n", myLinkList -> Head);
    fprintf(myLinkList -> FileGraph, "All:<f2> -> %d [color = \"#FFFFFF\"];\n", myLinkList -> Tail);
    fprintf(myLinkList -> FileGraph, "All:<f3> -> %d [color = \"#FFFFFF\"];\n", myLinkList -> Free);
    return 1;
}