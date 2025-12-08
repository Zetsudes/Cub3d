/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:43:17 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/08 12:43:36 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	is_map_null(char **map)
{
	if (!map)
	{
		printf("Error: Map is NULL\n");
		exit(1);
	}
}

static void	find_player(char **map, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	is_map_null(map);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				*player_x = x;
				*player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	printf("Error: Player start position not found\n");
	exit(1);
}

static int	can_flood(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
	{
		printf("Error: The map is not closed\n");
		exit(1);
	}
	if (map->data[y][x] == 'F')
		return (0);
	if (!is_traversable(map->data[y][x]))
		return (0);
	map->data[y][x] = 'F';
	return (1);
}

static void	flood_fill_recursive(t_map *map, int x, int y)
{
	int	dx[4];
	int	dy[4];
	int	i;

	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
	if (!can_flood(map, x, y))
		return ;
	i = 0;
	while (i < 4)
	{
		flood_fill_recursive(map, x + dx[i], y + dy[i]);
		i++;
	}
}

void	verify_map_copy(t_map *map)
{
	int	x;
	int	y;

	find_player(map->data, &map->player_start.x, &map->player_start.y);
	flood_fill_recursive(map, map->player_start.x, map->player_start.y);
	y = 0;
	while (map->data[y])
	{
		x = 0;
		while (map->data[y][x])
		{
			if (map->data[y][x] == 'F' && (y == 0 || map->data[y + 1] == NULL
					|| x == 0 || map->data[y][x + 1] == '\0'))
			{
				printf("Error: The map is not closed\n");
				exit(1);
			}
			x++;
		}
		y++;
	}
}
