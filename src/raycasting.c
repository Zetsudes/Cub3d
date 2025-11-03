/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:39 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/03 16:03:12 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// double	cast_one_ray(t_player *player, char **map, double ray_angle)
// {
// 	double x;
// 	double y;
// 	double dx;
// 	double dy;
// 	double distance;

// 	x = player->x;
// 	y = player->y;
// 	while (map[(int)y][(int)x] != '1')
// 	{
// 		x += cos(ray_angle) * STEP;
// 		y += cos(ray_angle) * STEP;
// 	}
// 	dx = x - player->x;
// 	dy = y - player->y;
// 	distance = sqrt(dx * dx + dy * dy);
// 	return (distance);
// }

// void cast_all_rays(t_player *player, char **map, t_data *data)
// {
//     int		x;
// 	double	ray_angle;
// 	double	start_angle;
// 	double	distance;

// 	start_angle = player->dir - (FOV / 2);
// 	x = 0;
// 	while (x < SCREEN_WIDTH)
// 	{
// 		ray_angle = start_angle + ((double)x / SCREEN_WIDTH) * FOV;
// 		distance = cast_one_ray(player, map, ray_angle);
// 		draw_wall(data, x, distance);
// 		x++;
// 	}
// }