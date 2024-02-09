#include "heap.h"

/**
 * do_insertion - Finds the parent node for inserting a new node
 * @root: Pointer to the root of the binary tree
 * @new: new node to be inserted
 *
 * Return: Pointer to the found parent node
 */
binary_tree_node_t *do_insertion(binary_tree_node_t *root,
											binary_tree_node_t *new)
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
		else
		{
			queue[index]->left = new;
			new->parent = queue[index];
			return (new);
		}
		if (queue[index]->right)
		{
			queue[num_ele] = queue[index]->right;
			num_ele++;
		}
		else
		{
			queue[index]->right = new;
			new->parent = queue[index];
			return (new);
		}
		index++;
	}
	return (NULL);
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
	binary_tree_node_t *new_node, *buffer;
	void *temp;

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

	do_insertion(heap->root, new_node);
	if (new_node)
		heap->size++;
	buffer = new_node;
	while (buffer->parent &&
			heap->data_cmp(buffer->data, buffer->parent->data) < 0)
	{
		temp = buffer->data;
		buffer->data = buffer->parent->data;
		buffer->parent->data = temp;
		buffer = buffer->parent;
	}
	new_node = buffer;
	return (new_node);
}
