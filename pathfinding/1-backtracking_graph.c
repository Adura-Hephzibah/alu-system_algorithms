#include "pathfinding.h"


/**
 * insert_town - adds a city to a queue
 *
 * @city: city name (string)
 * @queue: queue to place city in
 * Return: pointer to queue or NULL if city is NULL
 */
static queue_t *insert_town(char *city, queue_t *queue)
{
	if (!city)
	{
		queue_delete(queue);
		return (NULL);
	}
	queue_push_front(queue, city);
	return (queue);
}

/**
 * backtrack - helper backtracking algorithm
 *
 * @graph: pointer to graph
 * @tracked: pointer to array that keeps track of tracked cells
 * @curr: current position in graph
 * @target: target position
 * @path: pointer to queue where final path will be stored.
 * Return: pointer to path
 */
static queue_t *backtracker(graph_t *graph, char *tracked,
							vertex_t const *curr, vertex_t const *target, queue_t *path)
{
	edge_t *edge;

	if (!curr || tracked[curr->index])
		return (NULL);

	tracked[curr->index] = 1;

	printf("Checking %s\n", (char *)curr->content);

	if (curr == target)
		return (path);


	for (edge = curr->edges; edge; edge = edge->next)
		if (backtracker(graph, tracked, edge->dest, target, path))
			return (insert_town(strdup(edge->dest->content), path));

	return (NULL);
}


/**
 * backtracking_graph - searches for the first path from a starting point to a
 *                      target point in a graph.
 * @graph: pointer to the graph to go through
 * @start: pointer to the starting vertex
 * @target:pointer to the target vertex
 * Return: queue of strings corresponding to a vertex, forming a path from
 *         start to target
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	queue_t *path = NULL;
	char *tracked = NULL;

	if
	(
		!graph || !start || !target || !(path = queue_create()) ||
		!(tracked = calloc(graph->nb_vertices, sizeof(char))) ||
		!backtracker(graph, tracked, start, target, path)
	)
	{
		queue_delete(path);
		free(tracked);
		return (NULL);
	}

	free(tracked);
	return (insert_town(strdup(start->content), path));
}
