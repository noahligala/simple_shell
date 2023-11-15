#include "shell.h"

/**
 * displayHistory - displays the history list, one command by line, preceded
 *                  with line numbers, starting at 0.
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *             constant function prototype.
 *  Return: Always 0
 */
int displayHistory(info_t *shellInfo)
{
	print_list(shellInfo->history);
	return (0);
}

/**
 * removeAlias - removes alias from the list
 * @shellInfo: parameter struct
 * @aliasString: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int removeAlias(info_t *shellInfo, char *aliasString)
{
	char *equalSign, character;
	int result;

	equalSign = _strchr(aliasString, '=');
	if (!equalSign)
		return (1);

	character = *equalSign;
	*equalSign = 0;
	result = delete_node_at_index(&(shellInfo->alias),
		get_node_index(shellInfo->alias, node_starts_with(shellInfo->alias, aliasString, -1)));
	*equalSign = character;

	return result;
}

/**
 * addAlias - adds alias to the list
 * @shellInfo: parameter struct
 * @aliasString: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int addAlias(info_t *shellInfo, char *aliasString)
{
	char *equalSign;

	equalSign = _strchr(aliasString, '=');
	if (!equalSign)
		return (1);

	if (!*++equalSign)
		return (removeAlias(shellInfo, aliasString));

	removeAlias(shellInfo, aliasString);

	return (add_node_end(&(shellInfo->alias), aliasString, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @aliasNode: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *aliasNode)
{
	char *equalSign = NULL, *aliasStart = NULL;

	if (aliasNode)
	{
		equalSign = _strchr(aliasNode->str, '=');
		for (aliasStart = aliasNode->str; aliasStart <= equalSign; aliasStart++)
			_putchar(*aliasStart);
		_putchar('\'');
		_puts(equalSign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - mimics the alias builtin (man alias)
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *             constant function prototype.
 *  Return: Always 0
 */
int manageAlias(info_t *shellInfo)
{
	int index = 0;
	char *equalSign = NULL;
	list_t *aliasNode = NULL;

	if (shellInfo->argc == 1)
	{
		aliasNode = shellInfo->alias;
		while (aliasNode)
		{
			printAlias(aliasNode);
			aliasNode = aliasNode->next;
		}
		return (0);
	}
	for (index = 1; shellInfo->argv[index]; index++)
	{
		equalSign = _strchr(shellInfo->argv[index], '=');
		if (equalSign)
			addAlias(shellInfo, shellInfo->argv[index]);
		else
			printAlias(node_starts_with(shellInfo->alias, shellInfo->argv[index], '='));
	}

	return (0);
}
