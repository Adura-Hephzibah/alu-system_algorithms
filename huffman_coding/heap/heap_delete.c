#include "heap.h"

/**
 * delete_tree - Recursively frees the entire binary tree
 * @node: Pointer to the root of the binary tree
 * @free_data: Pointer to a function used to free the data in each node
 */
void delete_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	delete_tree(node->left, free_data);
	delete_tree(node->right, free_data);

	if (free_data != NULL)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - function that deallocates a heap
 * @heap: Pointer to the heap to delete
 * @free_data: pointer to a function that will be
 * used to free the content of a node
 * Return: Pointer to
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
		return;

	/* Free the entire tree starting at heap->root */
	delete_tree(heap->root, free_data);

	/* Free the heap structure itself */
	free(heap);
}
