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
		swap_nodes(node, smallest);
		heapify_down(heap, smallest);
	}
}

/**
 * find_last_node - Finds the last node in the heap
 * @root: Pointer to the root of the binary tree
 *
 * Return: Pointer to the last node
 */
binary_tree_node_t *find_last_node(binary_tree_node_t *root)
{
	binary_tree_node_t *queue[50];
	int index = 0, num_ele = 1, i, max_cap = 50;

	for (i = 0; i < max_cap; i++)
		queue[i] = NULL;

	queue[index] = root;
	while (queue[index])
	{
		if (queue[index]->left)
		{
			queue[num_ele] = queue[index]->left;
			num_ele++;
		}
		if (queue[index]->right)
		{
			queue[num_ele] = queue[index]->right;
			num_ele++;
		}
		index++;
	}

	return (queue[index - 1]);
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

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (source_data);
	}

	/* Find the last node */
	last_node = find_last_node(heap->root);


	/* Swap root with last node */
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
