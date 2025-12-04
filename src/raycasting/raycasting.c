/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:39 by zamohame          #+#    #+#             */
/*   Updated: 2025/12/04 13:41:33 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	setup_dda_variables(double r_dx, double r_dy, t_dda *dda)
{
	dda->delta_x = fabs(1.0 / r_dx);
	dda->delta_y = fabs(1.0 / r_dy);
}

static void	setup_dda_steps(t_player *p, double r_dx, double r_dy, t_dda *dda)
{
	if (r_dx < 0)
	{
		dda->step_x = -1;
		dda->side_x = (p->x - dda->map_x) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_x = (dda->map_x + 1.0 - p->x) * dda->delta_x;
	}
	if (r_dy < 0)
	{
		dda->step_y = -1;
		dda->side_y = (p->y - dda->map_y) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_y = (dda->map_y + 1.0 - p->y) * dda->delta_y;
	}
}

static double	perform_dda_loop(t_map *map, t_player *p, double r_dx,
		double r_dy, t_dda *dda, int *side)
{
	while (1)
	{
		if (dda->side_x < dda->side_y)
		{
			dda->side_x += dda->delta_x;
			dda->map_x += dda->step_x;
			*side = 0;
			dda->perp_dist = (dda->map_x - p->x + (1 - dda->step_x) / 2) / r_dx;
		}
		else
		{
			dda->side_y += dda->delta_y;
			dda->map_y += dda->step_y;
			*side = 1;
			dda->perp_dist = (dda->map_y - p->y + (1 - dda->step_y) / 2) / r_dy;
		}
		if (dda->map_x < 0 || dda->map_y < 0 || dda->map_x >= map->width
			|| dda->map_y >= map->height
			|| map->data[dda->map_y][dda->map_x] == '1')
			break ;
	}
	return (dda->perp_dist);
}

double	cast_one_ray(t_player *player, t_map *map, double ray_dx, double ray_dy,
		int *side)
{
	t_dda	dda;

	dda.map_x = (int)player->x;
	dda.map_y = (int)player->y;
	setup_dda_variables(ray_dx, ray_dy, &dda);
	setup_dda_steps(player, ray_dx, ray_dy, &dda);
	return (perform_dda_loop(map, player, ray_dx, ray_dy, &dda, side));
}

void	cast_all_rays(t_player *player, t_map *map, t_game *game)
{
	int			col;
	double		dist;
	t_wall_info	wall_data;
	double		camera_x_val;

	col = 0;
	while (col < win_width)
	{
		camera_x_val = 2.0 * (double)col / (double)win_width - 1.0;
		wall_data.ray_dx = player->dir_x + player->plane_x * camera_x_val;
		wall_data.ray_dy = player->dir_y + player->plane_y * camera_x_val;
		dist = cast_one_ray(player, map, wall_data.ray_dx, wall_data.ray_dy,
				&wall_data.side);
		wall_data.dist = dist;
		draw_wall(game, col, wall_data);
		col++;
	}
}
