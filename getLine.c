#include "shell.h"

/**
 * bufferChainedCommands - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t bufferChainedCommands(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t currentLength = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, interruptSignalHandler);
#if USE_GETLINE
		bytesRead = getline(buffer, &currentLength, stdin);
#else
		bytesRead = _getline(info, buffer, &currentLength);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
				bytesRead--;
			}
			info->lineCountFlag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->historyCount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*length = bytesRead;
				info->commandBuffer = buffer;
			}
		}
	}
	return bytesRead;
}

/**
 * getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *commandBuffer; /* the ';' command chain buffer */
	static size_t current, next, length;
	ssize_t bytesRead = 0;
	char **currentBufferPointer = &(info->arguments), *pointer;

	_putchar(BUF_FLUSH);
	bytesRead = bufferChainedCommands(info, &commandBuffer, &length);
	if (bytesRead == -1) /* EOF */
		return -1;

	if (length) /* we have commands left in the chain buffer */
	{
		next = current; /* init new iterator to current buffer position */
		pointer = commandBuffer + current; /* get pointer for return */

		checkChain(info, commandBuffer, &next, current, length);
		while (next < length) /* iterate to semicolon or end */
		{
			if (isChain(info, commandBuffer, &next))
				break;
			next++;
		}

		current = next + 1; /* increment past nulled ';'' */
		if (current >= length) /* reached end of buffer? */
		{
			current = length = 0; /* reset position and length */
			info->commandBufferType = CMD_NORM;
		}

		*currentBufferPointer = pointer; /* pass back pointer to current command position */
		return _strlen(pointer); /* return length of current command */
	}

	*currentBufferPointer = commandBuffer; /* else not a chain, pass back buffer from _getline() */
	return bytesRead; /* return length of buffer from _getline() */
}

/**
 * readBuffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @currentIndex: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *currentIndex)
{
	ssize_t bytesRead = 0;

	if (*currentIndex)
		return 0;
	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*currentIndex = bytesRead;
	return bytesRead;
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **pointer, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t currentIndex, currentLength;
	size_t k;
	ssize_t bytesRead = 0, size = 0;
	char *p = NULL, *newPointer = NULL, *c;

	p = *pointer;
	if (p && length)
		size = *length;
	if (currentIndex == currentLength)
		currentIndex = currentLength = 0;

	bytesRead = readBuffer(info, buffer, &currentLength);
	if (bytesRead == -1 || (bytesRead == 0 && currentLength == 0))
		return -1;

	c = _strchr(buffer + currentIndex, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : currentLength;
	newPointer = _realloc(p, size, size ? size + k : k + 1);
	if (!newPointer)
		return p ? free(p), -1 : -1;

	if (size)
		_strncat(newPointer, buffer + currentIndex, k - currentIndex);
	else
		_strncpy(newPointer, buffer + currentIndex, k - currentIndex + 1);

	size += k - currentIndex;
	currentIndex = k;
	p = newPointer;

	if (length)
		*length = size;
	*pointer = p;
	return size;
}

/**
 * interruptSignalHandler - blocks ctrl-C
 * @signalNumber: the signal number
 *
 * Return: void
 */
void interruptSignalHandler(__attribute__((unused))int signalNumber)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
