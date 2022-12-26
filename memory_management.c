#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "allocator.h"
#include "linked_list.h"
#include "json_handler.h"
int main(int argc, char const *argv[])
{

    initialize_list();
    initialize_memory();
    int8_t fit_mod = -1;
    char *filename;

    assert(("Invalid Arguments", !(argc % 2)));

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-f"))
        {
            filename = (char *)argv[++i];
        }
        else if (fit_mod >= 0)
        {
            fprintf(stderr, "%s\n", "Only one algorithm should be provider");
            abort();
        }
        else if (!strcmp(argv[i], "-ff"))
        {
            fit_mod = FIRST_FIT;
        }
        else if (!strcmp(argv[i], "-bf"))
        {
            fit_mod = BEST_FIT;
        }
        else if (!strcmp(argv[i], "-wf"))
        {
            fit_mod = WORST_FIT;
        }
    }

    if (filename != NULL && fit_mod >= 0)
    {
        json_deserialization(filename, fit_mod);
    }
    else
    {
        fprintf(stderr, "%s\n", "Wrong arguments provided \n");
        exit(1);
    }

    return 0;
}
