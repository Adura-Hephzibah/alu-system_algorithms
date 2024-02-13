#include "huffman.h"
#include "heap.h"

/**
 * huffman_extract_and_insert - extracts the two nodes of
 *								the priority queue and insert a new one
 * @priority_queue:  pointer to the priority queue to extract from
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *new_node, *node1, *node2;
	symbol_t *symbol;
	size_t combined_freq;

	if (!priority_queue || !priority_queue->root)
		return (0);

	/* Check if there are at least two nodes in the priority queue */
	if (priority_queue->size < 2)
		return (0);

	/*Extract the two nodes with the lowest frequencies*/
	node1 = heap_extract(priority_queue);
	node2 = heap_extract(priority_queue);

	if (!node1 || !node2)
		return (0);

	/* Combine the frequencies of the two nodes*/
	combined_freq = ((symbol_t *)node1->data)->freq +
														((symbol_t *)node2->data)->freq;

	symbol = malloc(sizeof(symbol_t));
	if (!symbol)
		return (0);

	symbol = symbol_create(-1, combined_freq);
	new_node = binary_tree_node(NULL, symbol);

	if (new_node == NULL)
    {
        free(symbol);
        return 0;
    }

	new_node->left = node1;
	new_node->right = node2;
	node1->parent = new_node;
	node2->parent = new_node;

	heap_insert(priority_queue, new_node);

	return (1);
}
