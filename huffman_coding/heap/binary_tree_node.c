#include "heap.h"

/**
 * binary_tree_node - function that creates a generic Binary Tree node
 *
 * @parent: pointer to the parent node of the node to be created
 * @data: data to be stored in the node
 *
 * Return: pointer to the created node or NULL if it fails
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new;

	new = malloc(sizeof(binary_tree_node_t));

	if (!new)
		return (NULL);

	new->data = data;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;

	return (new);
}
