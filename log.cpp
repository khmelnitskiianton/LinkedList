#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "main.h"
#include "log.h"
#include "ctor_dtor.h"

int PrintLogStart (DLinkList_t* myLinkList)
{
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

int PrintLogList (DLinkList_t* myLinkList)
{
    fprintf(myLinkList -> FileLog, "\n");

    GenerateGraph (myLinkList);
    GenerateImage (myLinkList);
    fprintf(myLinkList -> FileLog, "<img src=\"images/%lu.png\" alt=\"Человек и пароход\">\n", myLinkList -> NumImage);
    (myLinkList -> NumImage)++;

    return 1;
}

int GenerateGraph (DLinkList_t* myLinkList)
{
    myLinkList -> FileGraph = OpenFileGraph();

    fprintf (myLinkList -> FileGraph,   "digraph G{\n"
                                        "rankdir = LR;\n"
                                        "bgcolor = \"" FILL_BACK_COLOR "\";\n"
                                        "node[color = \"" COLOR_EDGE "\", fontsize = 10];\n"
                                        "edge[color = \"" COLOR_EDGE "\", fontsize = 15];\n"
                                        );

    fprintf(myLinkList -> FileGraph,    "subgraph cluster0 {\n"
                                        "\tnode[style = filled, color = white, fontsize = 10];\n"
                                        "\tedge[color = \"" COLOR_EDGE "\", fontsize = 15];\n"
                                        "\tstyle = \"dashed\";\n"
                                        "\tcolor = \"" "#800080" "\";\n"
                                        );

    WriteListToGraph(myLinkList);

    fprintf (myLinkList -> FileGraph,   "\tlabel = \"Double-Linked List\";\n"
                                        "}\n"
                                        "HEAD[shape = \"component\", label = \"Head | %d\", style = \"filled\", fillcolor = \"" FILL_BACK_LIST "\"];\n"
                                        "TAIL[shape = \"component\", label = \"Tail | %d\", style = \"filled\", fillcolor = \"" FILL_BACK_LIST "\"];\n"
                                        "FREE[shape = \"component\", label = \"Free | %d\", style = \"filled\", fillcolor = \"" FILL_BACK_LIST "\"];\n"
                                        "CAPACITY[shape = \"house\", label = \"Capacity | %d\", style = \"filled\", fillcolor = \"" FILL_BACK_LIST "\"];\n"
                                        "CAPACITY -> TAIL -> HEAD -> FREE [ color = \"" FILL_BACK_COLOR "\"];\n",
                                        myLinkList -> Head, myLinkList -> Tail, myLinkList -> Free, myLinkList -> Capacity
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
        fprintf (myLinkList -> FileGraph, "\t%d [shape = Mrecord, style = filled, fillcolor = \"" FILL_BACK_LIST "\", color = \"#d2691e\", label = \" IP: %d | DATA: " SPECIFIER " | NXT: %d | PRV: %d \"];\n", i, i, *(myLinkList -> Data + i), *(myLinkList -> Next + i), *(myLinkList -> Previous + i));
    }

    fprintf (myLinkList -> FileGraph, "\n\t");
    for (int i = 0; i < (myLinkList -> Capacity - 1); i++)
    {
        fprintf (myLinkList -> FileGraph, "%d -> ", i);
    }
    fprintf (myLinkList -> FileGraph, "%d [color = \"" FILL_BACK_COLOR "\"];\n\n");

    for (int i = 0; i < (myLinkList -> Capacity - 1); i++)
    {
        if (*(myLinkList -> Previous + i) == -1) fprintf (myLinkList -> FileGraph, "\t%d -> %d [color = \"#00ff00\"]\n", i, *(myLinkList -> Next + i));
        else fprintf (myLinkList -> FileGraph, "\t%d -> %d [color = \"#000000\"]\n", i, *(myLinkList -> Next + i));
    }
    return 1;
}

int WriteVarsToGraph(DLinkList_t* myLinkList)
{
    fprintf(myLinkList -> FileGraph, "HEAD -> %d [color = \"#7fffd4\"];\n", myLinkList -> Head);
    fprintf(myLinkList -> FileGraph, "TAIL -> %d [color = \"#7fffd4\"];\n", myLinkList -> Tail);
    fprintf(myLinkList -> FileGraph, "FREE -> %d [color = \"#7fffd4\"];\n", myLinkList -> Free);
    return 1;
}








/*
int printing_stack (DLinkList_t* myLinkList, const char* file, const size_t line, const char* pretty_function)
{
    fprintf (myLinkList -> FileLog,"\nStack[%p] called from %s (string: %lld) in function %s\n"
            "{                  \n"
            "\tsize        = %d \n"
            "\tcapacity    = %d \n"
            "\tdata[%p]         \n"
            "\t{                \n", myLinkList, file, line, pretty_function, myLinkList -> size, myLinkList -> capacity, ON_HASH(myLinkList -> hash_data, myLinkList -> hash_struct,) myLinkList -> data);

    for (ssize_t i = 0; (i < (myLinkList -> capacity)); i++)
    {
        if (i == (myLinkList -> size))                             fprintf(myLinkList -> FileLog,"\t >[%lld] = %d<\n", i, *((myLinkList -> data) + i));
        else if (*((myLinkList -> data) + i) != POISON_ELEMENT)    fprintf(myLinkList -> FileLog,"\t #[%lld] = %d\n", i, *((myLinkList -> data) + i));
        else                                                fprintf(myLinkList -> FileLog,"\t @[%lld] = %d(POISON)\n", i, *((myLinkList -> data) + i));
    }
    
    fprintf (myLinkList -> FileLog,"\t} \n"
            "}   \n");
    return 1;
}

int output_error (DLinkList_t* *myLinkList, const char* file, const size_t line, const char* pretty_function, int error_code)
{   
    const char* mass_of_errors[N_ERRORS] = {
        //TODO: array of errors
    };
    int z = error_code;
    unsigned long bin_error = 0;
    size_t element = 0;
    int fatal_error = 0;
    fprintf(myLinkList -> FileLog, "<<<<<!!!!YOU HAVE ERROR.CHECK OUTPUT.TXT OR TERMINAL!!!!>>>>>>>\n");
    if (z == 1)
    {
        fprintf(myLinkList -> FileLog, "\n<<<<<<<<<<<<<<<YOU HAVE ERROR>>>>>>>>>>>>>>>>>\n"
            "Stack[%p] called from %s (string: %lld) in function %s\n"
            "1: [%s]\n", myLinkList, file, line, pretty_function,mass_of_errors[0]);
        abort();
    }
    if (z == 2)
    {
        fprintf(myLinkList -> FileLog, "\n<<<<<<<<<<<<<<<YOU HAVE ERROR>>>>>>>>>>>>>>>>>\n"
            "Stack[%p] called from %s (string: %lld) in function %s\n"
            "0: [OK]\n"
            "1: [%s]\n", myLinkList, file, line, pretty_function,mass_of_errors[1]);
        abort();
    }

    fprintf(myLinkList -> FileLog, "\n<<<<<<<<<<<<<<<YOU HAVE ERROR>>>>>>>>>>>>>>>>>\n");
    fprintf(myLinkList -> FileLog, "\nERROR:\n");

    while (z > 0)
    {
        if (z % 2)
        {
            bin_error += 1<<(element);
            fprintf(myLinkList -> FileLog, "1: [%s]\n", mass_of_errors[element]);
            if(element != 15) fatal_error = 1;
        }
        else
        {
            fprintf(myLinkList -> FileLog, "0: [OK]\n");
        }
        z = z / 2;
        element++;
    }
    fprintf(myLinkList -> FileLog,"ERROR CODE: [%lu]\n\n", bin_error);
    
    if (!fatal_error)
    {
    fprintf (myLinkList -> FileLog,"Stack[%p] called from %s (string: %lld) in function %s\n"
    //      "\t\t%s             \n"
            "{                  \n"
            "\tsize        = %d \n"
            "\tcapacity    = %d \n"
            "\tdata[%p]         \n"
            "\t{                \n", myLinkList, file, line, pretty_function, myLinkList -> size, myLinkList -> capacity, ON_HASH(myLinkList -> hash_data, myLinkList -> hash_struct,) myLinkList -> data);

    for (ssize_t i = 0; (i < (myLinkList -> capacity)); i++)
    {
        if (i == myLinkList -> size)                               fprintf(myLinkList -> FileLog,"\t >[%lld] = %d<\n", i, *((myLinkList -> data) + i));
        else if (*((myLinkList -> data) + i) != POISON_ELEMENT)    fprintf(myLinkList -> FileLog,"\t #[%lld] = %d\n", i, *((myLinkList -> data) + i));
        else                                                fprintf(myLinkList -> FileLog,"\t @[%lld] = %d(POISON)\n", i, *((myLinkList -> data) + i));
    }
    
    fprintf (myLinkList -> FileLog,"\t} \n"
            "}   \n");
    }
    file_close(myLinkList -> FileLog);
    abort();
    return 1;
}

int checkStack (DLinkList_t* *myLinkList, const char* func)
{
    int error_code = 0;
    
    if (!myLinkList)                    
    {
        error_code |= 1<<0;
        return error_code;
    }
    if (!(myLinkList -> FileLog))                    
    {
        error_code |= 1<<1;
        return error_code;
    }

    if (!(myLinkList -> data))
    {
        error_code |= 1<<4;
        return error_code;
    }

    if ((strcmp(func, "int pop(Stack_t*, Elem_t*)") == 0)&&(!(myLinkList -> ret_value)))
    {
        error_code |= 1<<5;
        return error_code;
    }
    if ((myLinkList -> capacity) <= 0)             
    {
        error_code |= 1<<6;
        return error_code;
    }
        if ((myLinkList -> size) < 0)                  
    {
        error_code |= 1<<7;
        return error_code;
    }
    if ((myLinkList -> size) > (myLinkList -> capacity))  
    {
        error_code |= 1<<8;
        return error_code;
    }
    if ((strcmp(func, "int pop(Stack_t*, Elem_t*)") == 0)&&((myLinkList -> size) == 0)) 
    {
        error_code |= 1<<9;
        return error_code;
    }
    return error_code;
}
*/