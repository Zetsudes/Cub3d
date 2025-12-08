/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zetsu <zetsu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:36:18 by zamohame          #+#    #+#             */
/*   Updated: 2025/12/08 13:52:43 by zetsu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > win_width || y < 0 || y >= win_height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall(t_game *game, int x, t_wall_info ray_info)
{
	t_wall_info	w;

	w = ray_info;
	calculate_draw_parameters(game, &w);
	draw_vertical_strip(game, x, &w);
}

static int	create_trgb(int r, int g, int b)
{
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

static void	draw_background(t_game *game)
{
	int	ceiling_color;
	int	floor_color;
	int	x;
	int	y;

	ceiling_color = create_trgb(game->map.config.ceiling[0],
			game->map.config.ceiling[1], game->map.config.ceiling[2]);
	floor_color = create_trgb(game->map.config.floor[0],
			game->map.config.floor[1], game->map.config.floor[2]);
	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (x < win_width)
		{
			if (y < win_height / 2)
				my_mlx_pixel_put(&game->img, x, y, ceiling_color);
			else
				my_mlx_pixel_put(&game->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_background(game);
	cast_all_rays(&game->player, &game->map, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
