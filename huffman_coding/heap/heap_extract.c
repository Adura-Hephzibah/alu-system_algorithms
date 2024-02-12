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
		swap_nodes(smallest, node);
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

	if (heap == NULL || heap->root == NULL)
		return (NULL);


	/* Swap root with last node */
	binary_tree_node_t *last_node = NULL;
	binary_tree_node_t *temp = heap->root;

	while (temp->left != NULL || temp->right != NULL)
	{
		last_node = temp;
		if (temp->right != NULL && heap->data_cmp(temp->right->data,
													temp->left->data) < 0)
			temp = temp->right;
		else
			temp = temp->left;
	}

	if (last_node != NULL)
	{
		if (last_node->left == temp)
			last_node->left = NULL;
		else
			last_node->right = NULL;
	}

	if (last_node == NULL)
		heap->root = NULL;
	else
	{
		swap_nodes(heap->root, temp);
		heapify_down(heap, heap->root);
	}

	free(temp);
	heap->size--;

	return (source_data);
}
