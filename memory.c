#include "shell.h"

/**
 * freeAndNull - Frees a pointer and sets it to NULL.
 * @ptr: Pointer to be freed and set to NULL.
 *
 * Returns: (1) if freed successfully, otherwise (0).
 */
int freeAndNull(void **ptr)
{
    if (ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}
