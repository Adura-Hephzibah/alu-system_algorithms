#include "huffman.h"
#include "heap.h"

/**
 * huffman_tree - function that builds the Huffman tree
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of queue
 * Return: pointer to the root node of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue = NULL;
	binary_tree_node_t *root_node = NULL;

	priority_queue = huffman_priority_queue(data, freq, size);

	if (!priority_queue)
		return (NULL);

	while (priority_queue->size > 1)
		huffman_extract_and_insert(priority_queue);

	root_node = (binary_tree_node_t *)heap_extract(priority_queue);
	heap_delete(priority_queue, NULL);
	return (root_node);
}
