#include "shell.h"

/**
 * convertStringToInteger - converts a string to an integer
 * @inputString: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int convertStringToInteger(char *inputString)
{
	int index = 0;
	unsigned long int result = 0;

	if (*inputString == '+')
		inputString++;
	for (index = 0;  inputString[index] != '\0'; index++)
	{
		if (inputString[index] >= '0' && inputString[index] <= '9')
		{
			result *= 10;
			result += (inputString[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printErrorInfo - prints an error message
 * @shellInfo: the parameter & return info struct
 * @errorString: string containing specified error type
 *
 * Return: Nothing
 */
void printErrorInfo(info_t *shellInfo, char *errorString)
{
	_eputs(shellInfo->functionName);
	_eputs(": ");
	printDecimal(shellInfo->lineCount, STDERR_FILENO);
	_eputs(": ");
	_eputs(shellInfo->arguments[0]);
	_eputs(": ");
	_eputs(errorString);
}

/**
 * printDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimal(int input, int fileDescriptor)
{
	int (*writeChar)(char, int) = writeCharToFD;
	int index, count = 0;
	unsigned int absoluteValue, current;

	if (fileDescriptor == STDERR_FILENO)
		writeChar = writeErrorChar;

	if (input < 0)
	{
		absoluteValue = -input;
		writeChar('-');
		count++;
	}
	else
		absoluteValue = input;

	current = absoluteValue;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absoluteValue / index)
		{
			writeChar('0' + current / index, fileDescriptor);
			count++;
		}
		current %= index;
	}
	writeChar('0' + current, fileDescriptor);
	count++;

	return (count);
}

/**
 * convertNumberToString - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convertNumberToString(long int num, int base, int flags)
{
	static char *characterArray;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	characterArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = characterArray[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removeComments - function replaces first instance of '#' with '\0'
 * @inputBuffer: address of the string to modify
 *
 * Return: Always 0;
 */
void removeComments(char *inputBuffer)
{
	int index;

	for (index = 0; inputBuffer[index] != '\0'; index++)
		if (inputBuffer[index] == '#' && (!index || inputBuffer[index - 1] == ' '))
		{
			inputBuffer[index] = '\0';
			break;
		}
}
