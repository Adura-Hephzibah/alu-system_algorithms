#include "heap.h"

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap in which the node has to be inserted
 * @data: Pointer containing the data to store in the new node
 *
 * Return: Pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;
	size_t index;

	if (!heap || !data)
		return (NULL);

	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);

	if (!heap->root)
	{
		heap->root = new_node;
		heap->size++;
		return (new_node);
	}

	/* Find the parent to insert new node */
	index = heap->size + 1;
	parent = heap->root;
	while (index / 2 != 0)
	{
		parent = (index % 2 == 0) ? parent->left : parent->right;
		index /= 2;
	}

	/* Insert new node */
	new_node->parent = parent;
	if (!parent->left)
		parent->left = new_node;
	else
		parent->right = new_node;

	heap->size++;

	/* Restore heap property */
	while (new_node->parent && heap->data_cmp(new_node->data,
												new_node->parent->data) < 0)
	{
		/* Swap new node with parent */
		void *temp_data = (int *)new_node->data;

		new_node->data = new_node->parent->data;
		new_node->parent->data = temp_data;

		new_node = new_node->parent;
	}

	return (new_node);
}
