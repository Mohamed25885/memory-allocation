#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "allocator.h"
void run_free_worker(struct json_object *processes_obj);
void run_allocate_worker(struct json_object *process_array_obj, int mode);
void json_deserialization(char *filename, int mode)
{
    struct json_object *processes_obj,
        *process_array,
        *process_array_obj,
        *process_array_obj_type /* ,
                                 *process_array_obj_name,
                                 *process_array_obj_size,
                                 */
        ;
    int arraylen, i;

    processes_obj = json_object_from_file(filename);
    process_array = json_object_object_get(processes_obj, "processes");

    // process_array is an array of objects
    arraylen = json_object_array_length(process_array);

    for (i = 0; i < arraylen; i++)
    {
        // get the i-th object in process_array
        process_array_obj = json_object_array_get_idx(process_array, i);
        // get the name attribute in the i-th object
        process_array_obj_type = json_object_object_get(process_array_obj, "type");
        printf("%d\t", i);
        if (!strcmp(json_object_get_string(process_array_obj_type), "allocate"))
        {

            run_allocate_worker(process_array_obj, mode);
        }
        else if (!strcmp(json_object_get_string(process_array_obj_type), "free"))
        {
        }
        else
        {
            fprintf(stderr, "Undefined Type: %s", json_object_get_string(process_array_obj_type));
        }
        printf("\n");
    }
}

void run_allocate_worker(struct json_object *process_array_obj, int mode)
{
    struct json_object *process_array_obj_size = json_object_object_get(process_array_obj, "size");
    struct json_object *process_array_obj_name = json_object_object_get(process_array_obj, "name");
    allocate_memory(json_object_get_int(process_array_obj_size), json_object_get_string(process_array_obj_name), mode);
}

void run_free_worker(struct json_object *process_array_obj)
{
    struct json_object *process_array_obj_name = json_object_object_get(process_array_obj, "name");
    free_memory_with_name(json_object_get_string(process_array_obj_name));
}