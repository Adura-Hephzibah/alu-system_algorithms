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
	binary_tree_node_t *new_node, *parent, *temp;
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

	parent = heap->root;
	for (size_t index = heap->size + 1; index > 1; index >>= 1, parent = temp)
	{
		temp = (index & 1) ? parent->right : parent->left;
		if (!temp)
			temp = parent;
	}

	new_node->parent = parent;
	if (parent->left)
		parent->right = new_node;
	else
		parent->left = new_node;

	heap->size++;

	while (new_node->parent && heap->data_cmp(new_node->data, new_node->parent->data) < 0)
	{
		temp = new_node->parent;
		new_node->parent = temp->parent;
		temp->parent = new_node;
		if (temp->parent)
		{
			if (temp->parent->left == temp)
				temp->parent->left = new_node;
			else
				temp->parent->right = new_node;
		}

		if (new_node->left == temp)
		{
			new_node->left = temp->left;
			if (new_node->left)
				new_node->left->parent = new_node;
			temp->left = new_node->right;
			if (temp->left)
				temp->left->parent = temp;
			new_node->right = temp;
		}
		else
		{
			new_node->right = temp->right;
			if (new_node->right)
				new_node->right->parent = new_node;
			temp->right = new_node->left;
			if (temp->right)
				temp->right->parent = temp;
			new_node->left = temp;
		}
	}

	return (new_node);

}
