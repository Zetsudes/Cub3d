/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:36:18 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/03 15:59:35 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > 800 || y < 0 || y >= 600)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_data *img, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

double cast_one_ray(t_player *player, char **map, double ray_angle, t_data *img)
{
	double x;
	double y;
	int row;
	int col;
	
	x = player->x;
	y = player->y;
	row = (int)y;
	col = (int)x;
	while (map[row][col] != '1')
	{
		x += cos(ray_angle) * step_size;
		y += cos(ray_angle) * step_size;
		row = (int)y;
		col = (int)x;
		my_mlx_pixel_put(img, (int)(x * tile_size), (int)(y * tile_size), 0x00FF00);
	}
	double dx = x - player->x;
	double dy = y - player->y;
	double distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

void	draw_minimap(t_data *img, char **map, t_player *player)
{
	int row;
	int col;
	int color;
	int x;
	int y;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == '1')
				color = 0x888888;
			else
				color = 0x000000;
			draw_tile(img, col * tile_size, row * tile_size, color);
			col++;
		}
		row++;
	}
	x = (int)(player->x * tile_size);
	y = (int)(player->y * tile_size);
	my_mlx_pixel_put(img, x, y, 0xFF0000);
}
