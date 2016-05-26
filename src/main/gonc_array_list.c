#include <stdlib.h>
#include <string.h>
#include "gonc_array_list.h"

struct gonc_array_list* gonc_array_list_create(size_t capacity, size_t data_size)
{
    struct gonc_array_list* array_list = malloc(sizeof(struct gonc_array_list));
    array_list->array = calloc(capacity, sizeof(void*));
    array_list->capacity = capacity;
    array_list->data_size = data_size;
    array_list->size = 0;
    return array_list;
}

int gonc_array_list_set(struct gonc_array_list* array_list, size_t index, void* data)
{
    if(index >= array_list->size || index < 0) return -1;
    memcpy((char*)(array_list->array) + (index * array_list->data_size), data, array_list->data_size);
}

int gonc_array_list_append(struct gonc_array_list* array_list, void* data)
{
    if(array_list->size >= array_list->capacity)
    {
        array_list->capacity *= 2;
        array_list->array = realloc(array_list->array, array_list->capacity); 
    }
    memcpy((char*)(array_list->array) + (array_list->size * array_list->data_size), data, array_list->data_size);
    ++(array_list->size);
    return 0;
}

int gonc_array_list_insert(struct gonc_array_list* array_list, size_t index, void* data)
{
    if(index + 1 >= array_list->size || index < 0) return -1;
    if(array_list->size >= array_list->capacity)
    {
        array_list->capacity *= 2;
        array_list->array = realloc(array_list->array, array_list->capacity);
    }
    memmove((char*)(array_list->array) + ((index + 1) * array_list->data_size),
         (char*)(array_list->array) + (index * array_list->data_size),
         (array_list->size - index) * array_list->data_size);
    memcpy((char*)(array_list->array) + (index * array_list->data_size), data, array_list->data_size);
    ++(array_list->size);
    return 0;
}

int gonc_array_list_get(struct gonc_array_list* array_list, size_t index, void* data)
{
    if(index >= array_list->size || index < 0) return -1;
    memcpy(data, (char*)(array_list->array) + (index * array_list->data_size), array_list->data_size);
    return 0;
}

int gonc_array_list_remove(struct gonc_array_list* array_list, size_t index, void* data)
{
    if(index + 1 >= array_list->size || index < 0) return -1;
    memcpy(data, (char*)(array_list->array) + (index * array_list->data_size), array_list->data_size);
    memmove((char*)(array_list->array) + (index * array_list->data_size),
         (char*)(array_list->array) + ((index + 1) * array_list->data_size),
         (array_list->size - index) * array_list->data_size);
    --(array_list->size);
    return 0;
}

int gonc_array_list_compact(struct gonc_array_list* array_list)
{
    array_list->capacity = array_list->size;
    array_list->array = realloc(array_list->array, array_list->capacity);
    if(array_list->array != NULL) return 0;
    else return -1;
}