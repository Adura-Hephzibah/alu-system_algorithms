#include "heap.h"

/**
 * swap_data - Swaps the data of two binary tree nodes.
 * @a: Pointer to the first node.
 * @b: Pointer to the second node.
 */
void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *temp = a->data;

	a->data = b->data;
	b->data = temp;
}

/**
 * heapify_down - Restores the heap property by moving down the heap.
 * @heap: Pointer to the binary heap.
 */
void heapify_down(heap_t *heap)
{
	binary_tree_node_t *current = heap->root;
	binary_tree_node_t *child;

	while (current)
	{
		child = current->left;

		if (!child)
			break;

		if (current->right && heap->data_cmp(current->right->data, child->data) < 0)
			child = current->right;

		if (heap->data_cmp(current->data, child->data) > 0)
		{
			swap_data(current, child);
			current = child;
		}
		else
		{
			break;
		}
	}
}

/**
 * heap_extract - function that extracts the root value of a Min Binary Heap
 * @heap: pointer to the heap from which to extract the value
 *
 * Return: Pointer to the  data that was stored in the root node,
 * or NULL if it fails
 */
void *heap_extract(heap_t *heap)
{
	if (!heap || !heap->root)
		return (NULL);

	void *root_data;
	binary_tree_node_t *last_node;
	binary_tree_node_t *current;

	root_data = heap->root->data;
	last_node = heap->root;
	current = heap->root;

	/* Find the last node of the heap */
	while (last_node->left)
	{
		if (!last_node->right)
			last_node = last_node->left;
		else
		{
			if (heap->data_cmp(last_node->left->data, last_node->right->data) <= 0)
				last_node = last_node->left;
			else
				last_node = last_node->right;
		}
	}

	/* Replace root with last node */
	swap_data(heap->root, last_node);

	/* Detach last node from heap */
	if (last_node->parent->left == last_node)
		last_node->parent->left = NULL;
	else
		last_node->parent->right = NULL;

	/* Free last node */
	free(last_node);

	/* Restore heap property */
	heapify_down(heap);
	return (root_data);
}
