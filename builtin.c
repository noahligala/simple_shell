#include "shell.h"

/**
 * customExit - exits the shell
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if shellInfo->arguments[0] != "exit"
 */
int customExit(info_t *shellInfo)
{
	int exitStatus;

	if (shellInfo->arguments[1])  /* If there is an exit argument */
	{
		exitStatus = _erratoi(shellInfo->arguments[1]);
		if (exitStatus == -1)
		{
			shellInfo->status = 2;
			print_error(shellInfo, "Illegal number: ");
			_eputs(shellInfo->arguments[1]);
			_eputchar('\n');
			return (1);
		}
		shellInfo->err_num = _erratoi(shellInfo->arguments[1]);
		return (-2);
	}
	shellInfo->err_num = -1;
	return (-2);
}

/**
 * customCd - changes the current directory of the process
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int customCd(info_t *shellInfo)
{
	char *currentDir, *targetDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!shellInfo->arguments[1])
	{
		targetDir = _getenv(shellInfo, "HOME=");
		if (!targetDir)
			chdirResult = /* TODO: what should this be? */
				chdir((targetDir = _getenv(shellInfo, "PWD=")) ? targetDir : "/");
		else
			chdirResult = chdir(targetDir);
	}
	else if (_strcmp(shellInfo->arguments[1], "-") == 0)
	{
		if (!_getenv(shellInfo, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(shellInfo, "OLDPWD=")), _putchar('\n');
		chdirResult = /* TODO: what should this be? */
			chdir((targetDir = _getenv(shellInfo, "OLDPWD=")) ? targetDir : "/");
	}
	else
		chdirResult = chdir(shellInfo->arguments[1]);

	if (chdirResult == -1)
	{
		print_error(shellInfo, "can't cd to ");
		_eputs(shellInfo->arguments[1]), _eputchar('\n');
	}
	else
	{
		_setenv(shellInfo, "OLDPWD", _getenv(shellInfo, "PWD="));
		_setenv(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * customHelp - displays help information
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int customHelp(info_t *shellInfo)
{
	char **argumentArray;

	argumentArray = shellInfo->arguments;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argumentArray); /* temp att_unused workaround */
	return (0);
}
