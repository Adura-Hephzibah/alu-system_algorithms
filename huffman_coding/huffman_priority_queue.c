#include "huffman.h"
#include "heap.h"

/**
 * freq_cmp - Compares the frequencies of two symbols for heap ordering.
 *
 * @fq1: Pointer to the first symbol.
 * @fq2: Pointer to the second symbol.
 *
 * Return: The difference in frequencies (f1 - f2).
 */
int freq_cmp(void *fq1, void *fq2)
{
	symbol_t *sym1, *sym2;
	binary_tree_node_t *node1, *node2;

	node1 = (binary_tree_node_t *)fq1;
	node2 = (binary_tree_node_t *)fq2;
	sym1 = (symbol_t *)node1->data;
	sym2 = (symbol_t *)node2->data;

	return ((int)sym1->freq - (int)sym2->freq);
}

/**
 * huffman_priority_queue - creates a priority queue
 *							for the Huffman coding algorithm
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of queue
 * Return: pointer to the created min heap (also called priority queue)
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	symbol_t *sym = NULL;
	heap_t *new_heap = NULL;
	binary_tree_node_t *new_node = NULL;
	size_t index = 0;

	new_heap = heap_create(freq_cmp);

	if (!new_heap)
		return (NULL);
	new_heap->root = NULL;

	while (index < size)
	{
		sym = symbol_create(data[index], freq[index]);
		new_node = binary_tree_node(NULL, sym);
		/* heap_insert(new_heap, new_node); */
		if (!heap_insert(new_heap, new_node))
		{
			free(sym);
			free(new_node);
			return (NULL);
		}
		index++;
	}

	return (new_heap);
}
