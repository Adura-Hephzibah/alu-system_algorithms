#include "heap.h"

/**
 * swap_nodes - Swaps two nodes in a binary tree
 * @node1: Pointer to the first node
 * @node2: Pointer to the second node
 */
void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *temp_data = node1->data;

	node1->data = node2->data;
	node2->data = temp_data;
}

/**
 * get_last_node - Finds the last node from left to right at the last level
 * @heap: Pointer to the heap
 * Return: Pointer to the last node
 */
binary_tree_node_t *get_last_node(heap_t *heap)
{
	size_t size = heap->size;
	size_t level = 0;
	binary_tree_node_t *last_node = heap->root;

	while (last_node != NULL && size > 1)
	{
		if (size % 2 == 1)
			last_node = last_node->right;
		else
			last_node = last_node->left;

		size = size / 2;
		level++;
	}

	return (last_node);
}

/**
 * heapify_down - Heapifies down from the given node
 * @heap: Pointer to the heap
 * @node: Pointer to the node from which to start heapifying down
 */
void heapify_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest = node;
	binary_tree_node_t *left = node->left;
	binary_tree_node_t *right = node->right;

	if (left != NULL && heap->data_cmp(left->data, smallest->data) < 0)
		smallest = left;
	if (right != NULL && heap->data_cmp(right->data, smallest->data) < 0)
		smallest = right;

	if (smallest != node)
	{
		swap_nodes(node, smallest);
		heapify_down(heap, smallest);
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: Pointer to the heap from which to extract the value
 * Return: Pointer to the data that was stored in the root node of the heap,
 *         or NULL if the function fails or heap is NULL
 */
void *heap_extract(heap_t *heap)
{
	void *source_data = heap->root->data;
	binary_tree_node_t *last_node;

	if (heap == NULL || heap->root == NULL)
		return (NULL);


	/* Swap root with last node */
	last_node = get_last_node(heap);
	swap_nodes(heap->root, last_node);

	/* Remove last node */
	if (last_node->parent->left == last_node)
		last_node->parent->left = NULL;
	else
		last_node->parent->right = NULL;

	free(last_node);
	heap->size--;

	/* Heapify down */
	heapify_down(heap, heap->root);

	return (source_data);
}
