#include "shell.h"

/**
 * isInteractive - returns true if shell is in interactive mode
 * @infoStruct: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int isInteractive(info_t *infoStruct)
{
	return (isatty(STDIN_FILENO) && infoStruct->readfd <= 2);
}

/**
 * isDelimiter - checks if character is a delimiter
 * @character: the char to check
 * @delimiterString: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char character, char *delimiterString)
{
	while (*delimiterString)
		if (*delimiterString++ == character)
			return (1);
	return (0);
}

/**
 * isAlphabetic - checks for alphabetic character
 * @charValue: The character to input
 * Return: 1 if charValue is alphabetic, 0 otherwise
 */
int isAlphabetic(int charValue)
{
	if ((charValue >= 'a' && charValue <= 'z') || (charValue >= 'A' && charValue <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertToInteger - converts a string to an integer
 * @inputString: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convertToInteger(char *inputString)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0;  inputString[index] != '\0' && flag != 2; index++)
	{
		if (inputString[index] == '-')
			sign *= -1;

		if (inputString[index] >= '0' && inputString[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (inputString[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
