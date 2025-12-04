/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zetsu <zetsu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:36:18 by zamohame          #+#    #+#             */
/*   Updated: 2025/12/04 02:45:46 by zetsu            ###   ########.fr       */
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

// void	draw_tile(t_data *img, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < tile_size)
// 	{
// 		j = 0;
// 		while (j < tile_size)
// 		{
// 			my_mlx_pixel_put(img, x + j, y + i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void draw_wall(t_game *game, int x, double dist, int side, double ray_dx, double ray_dy)
{
    int     line_height;
    int     top, bottom;
    int     tex_x, tex_id;
    double  step, tex_pos;
    t_data  *tex;
    int     y;

    if (dist < 0.0001) dist = 0.0001; 
    line_height = (int)((double)win_height / dist);
    top = (win_height / 2) - (line_height / 2);
    bottom = (win_height / 2) + (line_height / 2);
    if (top < 0) top = 0;
    if (bottom >= win_height) bottom = win_height - 1;
    get_tex_x_id(game, dist, side, ray_dx, ray_dy, &tex_id, &tex_x);
    tex = &game->textures[tex_id];
	step = 1.0 * tex->height / line_height;
    tex_pos = (top - win_height / 2 + line_height / 2) * step;

    y = top; 
    while (y <= bottom)
    {
        int tex_y = (int)tex_pos & (tex->height - 1); 
        tex_pos += step;
        
        int color = get_texture_pixel(tex, tex_x, tex_y);
        if (side == 1)
            color = (color >> 1) & 8355711;
            
        my_mlx_pixel_put(&game->img, x, y, color);
        y++;
    }
}

// void	draw_minimap(t_data *img, char **map, t_player *player)
// {
// 	int	row;
// 	int	col;
// 	int	color;
// 	int	x;
// 	int	y;

// 	row = 0;
// 	while (map[row])
// 	{
// 		col = 0;
// 		while (map[row][col])
// 		{
// 			if (map[row][col] == '1')
// 				color = 0x888888;
// 			else
// 				color = 0x000000;
// 			draw_tile(img, col * tile_size, row * tile_size, color);
// 			col++;
// 		}
// 		row++;
// 	}
// 	x = (int)(player->x * tile_size);
// 	y = (int)(player->y * tile_size);
// 	my_mlx_pixel_put(img, x, y, 0xFF0000);
// }

static int create_trgb(int r, int g, int b)
{
    // Sets Alpha to 0xFF (fully opaque) and shifts R, G, B into place.
    return (0xFF000000 | (r << 16) | (g << 8) | b);
}

// Add this helper function (e.g., in render.c or a new draw_utils.c)
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
			if (y < win_height / 2) // Top half is Ceiling
				my_mlx_pixel_put(&game->img, x, y, ceiling_color);
			else // Bottom half is Floor
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
