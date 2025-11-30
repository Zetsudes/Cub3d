/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:04:56 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/29 21:29:52 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	check_flood_conditions(char **map_copy, int x, int y, int width, int height)
{
	if (y < 0 || x < 0 || x >= width || y >= height)
	{
		printf("Error: The map_copy is not closed\n");
		exit(1);
	}
	check_valid_char(map_copy[y][x]);
	if (is_filled_or_wall(map_copy[y][x]))
		return;
}

static void	flood_fill_recursive(char **map_copy, int x, int y, int width, int height)
{
	int	dx[4];
	int	dy[4];
	int	i;

	map_copy[y][x] = 'F';
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
		if (is_traversable(map_copy[y + dy[i]][x + dx[i]]))
			flood_fill_recursive(map_copy, x + dx[i], y + dy[i], width, height);
		i++;
	}
}

static void	flood_fill(char **map_copy, int x, int y, int width, int height)
{
	check_flood_conditions(map_copy, x, y, width, height);
	if (is_traversable(map_copy[y][x]))
		flood_fill_recursive(map_copy, x, y, width, height);
}

void	verify_map_copy(char **map_copy, int player_x, int player_y, int width, int height)
{
	int	x;
	int	y;

	flood_fill(map_copy, player_x, player_y, width, height);
	y = 0;
	while (map_copy[y])
	{
				x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'F' && (y == 0 || map_copy[y + 1] == NULL
				|| x == 0 || map_copy[y][x + 1] == '\0'))
			{
				printf("Error: The map_copy is not closed\n");
				exit(1);
			}
			x++;
		}
		y++;
	}
	printf("map_copy is closed and valid!\n");
}


