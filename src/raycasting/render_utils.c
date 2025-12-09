/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:42:24 by zamohame          #+#    #+#             */
/*   Updated: 2025/12/09 08:25:03 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	calculate_draw_parameters(t_game *game, t_wall_info *info)
{
	int		line_height;
	int		tex_id;
	double	step;
	double	temp_dist;

	temp_dist = info->dist;
	if (temp_dist < 0.0001)
		temp_dist = 0.0001;
	line_height = (int)((double)WIN_HEIGHT / temp_dist);
	info->draw_start = (WIN_HEIGHT / 2) - (line_height / 2);
	info->draw_end = (WIN_HEIGHT / 2) + (line_height / 2);
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= WIN_HEIGHT)
		info->draw_end = WIN_HEIGHT - 1;
	get_tex_x_id(game, info, &tex_id, &info->tex_x);
	info->texture = &game->textures[tex_id];
	step = 1.0 * info->texture->height / line_height;
	info->tex_pos = (info->draw_start - WIN_HEIGHT / 2 + line_height / 2)
		* step;
	info->tex_step = step;
}

void	draw_vertical_strip(t_game *game, int x, t_wall_info *info)
{
	int		y;
	int		tex_y;
	int		color;
	double	tex_pos;
	int		final_color;

	tex_pos = info->tex_pos;
	y = info->draw_start;
	while (y <= info->draw_end)
	{
		tex_y = (int)tex_pos & (info->texture->height - 1);
		tex_pos += info->tex_step;
		color = get_texture_pixel(info->texture, info->tex_x, tex_y);
		final_color = color;
		if (info->side == 1)
			final_color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&game->img, x, y, final_color);
		y++;
	}
}
