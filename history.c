#include "shell.h"

/**
 * obtainHistoryFilePath - gets the history file path
 * @info: parameter struct
 *
 * Return: allocated string containing the history file path
 */
char *obtainHistoryFilePath(info_t *info)
{
	char *filePath, *homeDirectory;

	homeDirectory = _getenv(info, "HOME=");
	if (!homeDirectory)
		return (NULL);

	filePath = malloc(sizeof(char) * (_strlen(homeDirectory) + _strlen(HISTORY_FILE) + 2));
	if (!filePath)
		return (NULL);

	filePath[0] = '\0';
	_strcpy(filePath, homeDirectory);
	_strcat(filePath, "/");
	_strcat(filePath, HISTORY_FILE);

	return (filePath);
}

/**
 * saveHistoryToFile - creates a file or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int saveHistoryToFile(info_t *info)
{
	ssize_t fileDescriptor;
	char *filename = obtainHistoryFilePath(info);
	list_t *historyNode = NULL;

	if (!filename)
		return (-1);

	fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fileDescriptor == -1)
		return (-1);

	for (historyNode = info->history; historyNode; historyNode = historyNode->next)
	{
		_putsfd(historyNode->str, fileDescriptor);
		_putfd('\n', fileDescriptor);
	}

	_putfd(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);

	return (1);
}

/**
 * loadHistoryFromFile - reads history from file
 * @info: the parameter struct
 *
 * Return: updated history count on success, 0 otherwise
 */
int loadHistoryFromFile(info_t *info)
{
	int i, last = 0, lineCount = 0;
	ssize_t fileDescriptor, bytesRead, fileSize = 0;
	struct stat fileStat;
	char *buffer = NULL, *filename = obtainHistoryFilePath(info);

	if (!filename)
		return (0);

	fileDescriptor = open(filename, O_RDONLY);
	free(filename);

	if (fileDescriptor == -1)
		return (0);

	if (!fstat(fileDescriptor, &fileStat))
		fileSize = fileStat.st_size;

	if (fileSize < 2)
		return (0);

	buffer = malloc(sizeof(char) * (fileSize + 1));
	if (!buffer)
		return (0);

	bytesRead = read(fileDescriptor, buffer, fileSize);
	buffer[fileSize] = '\0';

	if (bytesRead <= 0)
		return (free(buffer), 0);

	close(fileDescriptor);

	for (i = 0; i < fileSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			buildHistoryList(info, buffer + last, lineCount++);
			last = i + 1;
		}

	if (last != i)
		buildHistoryList(info, buffer + last, lineCount++);

	free(buffer);
	info->historyCount = lineCount;

	while (info->historyCount-- >= HISTORY_MAX)
		deleteNodeAtIndex(&(info->history), 0);

	recomputeHistoryNumbers(info);

	return (info->historyCount);
}

/**
 * buildHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @lineCount: the history line count
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buffer, int lineCount)
{
	list_t *historyNode = NULL;

	if (info->history)
		historyNode = info->history;

	addNodeEnd(&historyNode, buffer, lineCount);

	if (!info->history)
		info->history = historyNode;

	return (0);
}

/**
 * recomputeHistoryNumbers - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new history count
 */
int recomputeHistoryNumbers(info_t *info)
{
	list_t *historyNode = info->history;
	int i = 0;

	while (historyNode)
	{
		historyNode->num = i++;
		historyNode = historyNode->next;
	}

	return (info->historyCount = i);
}
