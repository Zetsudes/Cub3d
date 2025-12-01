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


static void	find_player(char **map, int *player_x, int *player_y)
{
	int y;
	int x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' ||
				map[y][x] == 'E' || map[y][x] == 'W')
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

static void	flood_fill_recursive(char **map_copy, int x, int y, int width, int height)
{
	int	dx[4];
	int	dy[4];
	int	i;

	if (x < 0 || y < 0 || x >= width || y >= height)
	{
        printf("Error: The map is not closed\n");
        exit(1);
    }
	if (map_copy[y][x] == 'F')
		return;
	if (!is_traversable(map_copy[y][x]))
		return;
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
		flood_fill_recursive(map_copy, x + dx[i], y + dy[i], width, height);
		i++;
	}
}

void	verify_map_copy(char **map_copy, int player_x, int player_y, int width, int height)
{
	//DEBUG
	for (int i=0; i <= height; i++) {
		dprintf(2, "%s", map_copy[i]);
	}
	dprintf(2, "\n=======================================\n");

	//END_DEBUG
	int	x;
	int	y;

	find_player(map_copy, &player_x, &player_y);
	flood_fill_recursive(map_copy, player_x, player_y, width, height);
	y = 0;
	while (map_copy[y])
	{
				x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'F' && (y == 0 || map_copy[y + 1] == NULL
				|| x == 0 || map_copy[y][x + 1] == '\0'))
			{
				printf("Conard: The map_copy is not closed\n");
				exit(1);
			}
			x++;
		}
		y++;
	}
}


