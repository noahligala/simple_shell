#include "shell.h"

/**
 * displayEnvironment - prints the current environment
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
int displayEnvironment(info_t *shellInfo)
{
	print_list_str(shellInfo->env);
	return (0);
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * @variableName: environment variable name
 *
 * Return: the value
 */
char *getEnvironmentVariable(info_t *shellInfo, const char *variableName)
{
	list_t *node = shellInfo->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, variableName);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *                          or modify an existing one
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0
 */
int setEnvironmentVariable(info_t *shellInfo)
{
	if (shellInfo->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(shellInfo, shellInfo->argv[1], shellInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
int unsetEnvironmentVariable(info_t *shellInfo)
{
	int i;

	if (shellInfo->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= shellInfo->argc; i++)
		_unsetenv(shellInfo, shellInfo->argv[i]);

	return (0);
}

/**
 * populateEnvironmentList - populates environment linked list
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *                  constant function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(info_t *shellInfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	shellInfo->env = node;
	return (0);
}
