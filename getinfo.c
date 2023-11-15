#include "shell.h"

/**
 * initializeInfo - initializes info_t struct
 * @info: struct address
 */
void initializeInfo(info_t *info)
{
	info->arguments = NULL;
	info->argumentVector = NULL;
	info->path = NULL;
	info->argumentCount = 0;
}

/**
 * fillInfo - initializes info_t struct
 * @info: struct address
 * @argumentVector: argument vector
 */
void fillInfo(info_t *info, char **argumentVector)
{
	int i = 0;

	info->executableName = argumentVector[0];
	if (info->arguments)
	{
		info->argumentVector = strtow(info->arguments, " \t");
		if (!info->argumentVector)
		{

			info->argumentVector = malloc(sizeof(char *) * 2);
			if (info->argumentVector)
			{
				info->argumentVector[0] = _strdup(info->arguments);
				info->argumentVector[1] = NULL;
			}
		}
		for (i = 0; info->argumentVector && info->argumentVector[i]; i++)
			;
		info->argumentCount = i;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * releaseInfo - frees info_t struct fields
 * @info: struct address
 * @freeAll: true if freeing all fields
 */
void releaseInfo(info_t *info, int freeAll)
{
	ffree(info->argumentVector);
	info->argumentVector = NULL;
	info->path = NULL;
	if (freeAll)
	{
		if (!info->commandBuffer)
			free(info->arguments);
		if (info->environment)
			freeList(&(info->environment));
		if (info->history)
			freeList(&(info->history));
		if (info->aliasList)
			freeList(&(info->aliasList));
		ffree(info->environmentStrings);
		info->environmentStrings = NULL;
		bfree((void **)info->commandBuffer);
		if (info->readFileDescriptor > 2)
			close(info->readFileDescriptor);
		_putchar(BUF_FLUSH);
	}
}
