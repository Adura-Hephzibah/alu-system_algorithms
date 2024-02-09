#include "heap.h"

/**
 * find_insertion_parent - Finds the parent node for inserting a new node
 * @root: Pointer to the root of the binary heap
 * @index: Index where the new node will be inserted
 *
 * Return: Pointer to the found parent node
 */
binary_tree_node_t *find_insertion_parent(binary_tree_node_t *root,
											size_t index)
{
	binary_tree_node_t *parent = root;
	binary_tree_node_t *temp;

	while (index > 1)
	{
		temp = (index & 1) ? parent->right : parent->left;
		if (!temp)
			temp = parent;
		index >>= 1;
		parent = temp;
	}

	return (parent);
}

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

	parent = find_insertion_parent(heap->root, heap->size + 1);
	new_node->parent = parent;
	if (!parent->left)
		parent->left = new_node;
	else
		parent->right = new_node;

	heap->size++;

	/* Restore heap property if necessary */
	while (new_node->parent && heap->data_cmp(new_node->data,
												new_node->parent->data) < 0)
	{
		/* Swap data between new_node and its parent */
		void *temp_data = new_node->data;

		new_node->data = new_node->parent->data;
		new_node->parent->data = temp_data;

		new_node = new_node->parent;
	}

	return (new_node);
}
