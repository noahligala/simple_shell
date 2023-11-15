#include "shell.h"

/**
 * addNodeAtStart - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: new head of the list
 */
list_t *addNodeAtStart(list_t **head, const char *str, int num)
{
	list_t *newHead;

	if (!head)
		return (NULL);

	newHead = malloc(sizeof(list_t));
	if (!newHead)
		return (NULL);

	_memset((void *)newHead, 0, sizeof(list_t));
	newHead->num = num;

	if (str)
	{
		newHead->str = _strdup(str);
		if (!newHead->str)
		{
			free(newHead);
			return (NULL);
		}
	}

	newHead->next = *head;
	*head = newHead;

	return (newHead);
}

/**
 * addNodeAtEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: new node added at the end
 */
list_t *addNodeAtEnd(list_t **head, const char *str, int num)
{
	list_t *newNode, *currentNode;

	if (!head)
		return (NULL);

	currentNode = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	if (currentNode)
	{
		while (currentNode->next)
			currentNode = currentNode->next;
		currentNode->next = newNode;
	}
	else
		*head = newNode;

	return (newNode);
}

/**
 * printListStrings - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t printListStrings(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		size++;
	}
	return (size);
}

/**
 * deleteNodeAtIndex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *currentNode, *prevNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		currentNode = *head;
		*head = (*head)->next;
		free(currentNode->str);
		free(currentNode);
		return (1);
	}

	currentNode = *head;
	while (currentNode)
	{
		if (i == index)
		{
			prevNode->next = currentNode->next;
			free(currentNode->str);
			free(currentNode);
			return (1);
		}
		i++;
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @headPtr: address of pointer to head node
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
	list_t *currentNode, *nextNode, *head;

	if (!headPtr || !*headPtr)
		return;

	head = *headPtr;
	currentNode = head;

	while (currentNode)
	{
		nextNode = currentNode->next;
		free(currentNode->str);
		free(currentNode);
		currentNode = nextNode;
	}

	*headPtr = NULL;
}
