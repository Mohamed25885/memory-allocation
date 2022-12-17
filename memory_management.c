#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "allocator.h"
#include "linked_list.h"
#include "json_handler.h"
int main(int argc, char const *argv[])
{

    initialize_list();
    initialize_memory();
    int fit_mod = -1;
    char *filename;

    assert(("Invalid Arguments", !(argc % 2)));

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-f"))
        {
            filename = (char *)argv[i + 1];
        }
        else if (!strcmp(argv[i], "-ff") && fit_mod < 0)
        {
            fit_mod = FIRST_FIT;
        }
        else if (!strcmp(argv[i], "-bf") && fit_mod < 0)
        {
            fit_mod = BEST_FIT;
        }
        else if (!strcmp(argv[i], "-wf") && fit_mod < 0)
        {
            fit_mod = WORST_FIT;
        }
    }

    if (filename != NULL && fit_mod >= 0)
    {
        json_deserialization(filename, fit_mod);
    }

    /*
     print_list();
     // print_memory();
     // getc(stdin); */
    return 0;
}
