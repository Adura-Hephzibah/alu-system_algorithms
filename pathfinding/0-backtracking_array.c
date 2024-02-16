#include "pathfinding.h"

/**
 * isValid - check if a given cell is valid
 * @map: the map to navigate
 * @rows: number of rows
 * @cols: number of cols
 * @x: the starting coordinates
 * @y: the target coordinates
 * Return: queue with the path to target
 */
bool isValid(char **map, int rows, int cols, int x, int y)
{
	return (x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] == '0');
}

/* Recursive function to find a path using backtracking */
bool findPath(char **map, int rows, int cols, point_t current,
																point_t const *target, queue_t *path)
{
	/* Check if the current point is the target */
	if (current.x == target->x && current.y == target->y)
	{
		/* Push the target point to the path queue */
		queue_push_back(path, (void *)&current);
		return (true);
	}

	/* Mark the current point as visited */
	map[current.x][current.y] = VISITED;

	/* Print the visited cell */
	printf("(%d, %d)\n", current.x, current.y);

	/* Define the order of exploration: RIGHT, BOTTOM, LEFT, TOP*/
	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};
	int i;

	for (i = 0; i < 4; i++)
	{
		int nextX = current.x + dx[i];
		int nextY = current.y + dy[i];

		/* Check if the next cell is valid and not visited */
		if (isValid(map, rows, cols, nextX, nextY))
		{
			queue_push_back(path, (void *)&current);

			/* Recursively explore the next cell */
			if (findPath(map, rows, cols, (point_t)
													{nextX, nextY}, target, path))
				return (true);

			queue_pop_back(path);
		}
	}

	/* If no path is found, mark the current cell as unvisited */
	map[current.x][current.y] = '0';
	return (false);
}

/**
 * backtracking_array - finds a path using backtracking
 * @map: the map to navigate
 * @rows: number of rows
 * @cols: number of cols
 * @start: the starting coordinates
 * @target: the target coordinates
 * Return: queue with the path to target
 */
queue_t *backtracking_array(char **map, int rows, int cols,
															point_t const *start, point_t const *target)
{
	/* Create a queue to store the path*/
	queue_t *path = queue_create();

	/* Check if the start and target points are valid */
	if (!isValid(map, rows, cols, start->x, start->y) ||
														!isValid(map, rows, cols, target->x, target->y))
	{
		fprintf(stderr, "Invalid start or target point\n");
		return (NULL);
	}

	/* Find the path using recursive backtracking */
	if (!findPath(map, rows, cols, *start, target, path))
	{
		fprintf(stderr, "No path found\n");
		queue_delete(path);
		return (NULL);
	}

	return (path);
}
