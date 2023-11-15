#include "shell.h"

/**
 * printErrorString - prints an error string
 * @errorStr: the string to be printed
 *
 * Return: Nothing
 */
void printErrorString(char *errorStr)
{
	int index = 0;

	if (!errorStr)
		return;
	while (errorStr[index] != '\0')
	{
		writeErrorChar(errorStr[index]);
		index++;
	}
}

/**
 * writeErrorChar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeErrorChar(char c)
{
	static int bufferIndex;
	static char writeBuffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
	{
		write(2, writeBuffer, bufferIndex);
		bufferIndex = 0;
	}
	if (c != BUF_FLUSH)
		writeBuffer[bufferIndex++] = c;
	return (1);
}

/**
 * writeCharToFD - writes the character c to a given file descriptor
 * @c: The character to print
 * @fileDescriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToFD(char c, int fileDescriptor)
{
	static int bufferIndex;
	static char writeBuffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
	{
		write(fileDescriptor, writeBuffer, bufferIndex);
		bufferIndex = 0;
	}
	if (c != BUF_FLUSH)
		writeBuffer[bufferIndex++] = c;
	return (1);
}

/**
 * printStringToFD - prints an input string to a given file descriptor
 * @str: the string to be printed
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int printStringToFD(char *str, int fileDescriptor)
{
	int charCount = 0;

	if (!str)
		return (0);
	while (*str)
	{
		charCount += writeCharToFD(*str++, fileDescriptor);
	}
	return (charCount);
}
