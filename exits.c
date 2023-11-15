#include "shell.h"

/**
 * copyStringN - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @maxCharacters: the maximum number of characters to be copied
 *
 * Return: the copied string
 */
char *copyStringN(char *destination, char *source, int maxCharacters)
{
	int index, j;
	char *result = destination;

	index = 0;
	while (source[index] != '\0' && index < maxCharacters - 1)
	{
		destination[index] = source[index];
		index++;
	}

	if (index < maxCharacters)
	{
		j = index;
		while (j < maxCharacters)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return result;
}

/**
 * concatenateStringsN - concatenates two strings
 * @destination: the first string
 * @source: the second string
 * @maxBytes: the maximum number of bytes to be used
 *
 * Return: the concatenated string
 */
char *concatenateStringsN(char *destination, char *source, int maxBytes)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;

	while (source[j] != '\0' && j < maxBytes)
	{
		destination[i] = source[j];
		i++;
		j++;
	}

	if (j < maxBytes)
		destination[i] = '\0';

	return result;
}

/**
 * findCharacter - locates a character in a string
 * @string: the string to be parsed
 * @character: the character to look for
 *
 * Return: (string) a pointer to the memory area string
 */
char *findCharacter(char *string, char character)
{
	do {
		if (*string == character)
			return string;
	} while (*string++ != '\0');

	return NULL;
}
