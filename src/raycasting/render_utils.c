
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
	line_height = (int)((double)win_height / temp_dist);
	info->draw_start = (win_height / 2) - (line_height / 2);
	info->draw_end = (win_height / 2) + (line_height / 2);
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= win_height)
		info->draw_end = win_height - 1;
	get_tex_x_id(game, temp_dist, info->side, info->ray_dx, info->ray_dy,
		&tex_id, &info->tex_x);
	info->texture = &game->textures[tex_id];
	step = 1.0 * info->texture->height / line_height;
	info->tex_pos = (info->draw_start - win_height / 2 + line_height / 2)
		* step;
	info->tex_step = step;
}

void	draw_vertical_strip(t_game *game, int x, t_wall_info *info)
{
	int y;
	int tex_y;
	int color;
	double tex_pos;
	int final_color;

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