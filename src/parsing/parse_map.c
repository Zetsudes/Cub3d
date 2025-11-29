/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:04:56 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/29 20:42:31 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	check_flood_conditions(char **map, int x, int y, int width, int height)
{
	if (y < 0 || x < 0 || x >= width || y >= height)
	{
		printf("Error: The map is not closed\n");
		exit(1);
	}
	check_valid_char(map[y][x]);
	if (is_filled_or_wall(map[y][x]))
		return;
}

static void	flood_fill_recursive(char **map, int x, int y, int width, int height)
{
	int	dx[4];
	int	dy[4];
	int	i;

	map[y][x] = 'F';
	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
	i = 0;
	while (i < 4)
	{
		if (is_traversable(map[y + dy[i]][x + dx[i]]))
			flood_fill_recursive(map, x + dx[i], y + dy[i], width, height);
		i++;
	}
}

static void	flood_fill(char **map, int x, int y, int width, int height)
{
	check_flood_conditions(map, x, y, width, height);
	if (is_traversable(map[y][x]))
		flood_fill_recursive(map, x, y, width, height);
}

void	verify_map(char **map, int player_x, int player_y, int width, int height)
{
	int	x;
	int	y;

	flood_fill(map, player_x, player_y, width, height);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'F' && (y == 0 || map[y + 1] == NULL
				|| x == 0 || map[y][x + 1] == '\0'))
			{
				printf("Error: The map is not closed\n");
				exit(1);
			}
			x++;
		}
		y++;
	}
	printf("Map is closed and valid!\n");
}


