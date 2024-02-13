#include "huffman.h"

/**
 * symbol_create - function that creates a symbol_t data structure
 * @data: data to be stored in the structure
 * @freq: associated frequency
 * Return: pointer to the created structure, or NULL if it fails
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *new;

	new = malloc(sizeof(symbol_t));

	if (!new)
		return (NULL);

	new->data = data;
	new->freq = freq;

	return (new);
}
