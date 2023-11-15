#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++) {
        s[i] = b;
    }
    return s;
}

/**
 * ffree - frees a string of strings
 * @str_arr: string of strings
 */
void ffree(char **str_arr)
{
    char **temp = str_arr;

    if (!str_arr)
        return;

    while (*str_arr) {
        free(*str_arr++);
    }
    free(temp);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to the allocated block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr) {
        return (malloc(new_size));
    }

    if (!new_size) {
        free(ptr);
        return (NULL);
    }

    if (new_size == old_size) {
        return (ptr);
    }

    new_ptr = malloc(new_size);
    if (!new_ptr) {
        return (NULL);  // Allocation failure
    }

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--) {
        new_ptr[old_size] = ((char *)ptr)[old_size];
    }

    free(ptr);
    return (new_ptr);
}
