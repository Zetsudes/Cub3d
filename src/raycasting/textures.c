
#include "raycasting.h"

void	load_texture(t_game *game, t_data *data, char *path)
{
	if (!path)
	{
		printf("oh no... no texture path (⁠╥⁠﹏⁠╥⁠)\n");
		exit(1);
	}
	data->img = mlx_xpm_file_to_image(game->mlx, path, &data->width,
			&data->height);
	if (!data->img)
	{
		printf("omygad... what is this image /ᐠ ╥ ˕ ╥マ ‹/𝟹\n");
		exit(1);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length,
			&data->endian);
	if (!data->addr)
	{
		printf("oh no... where's the address (╥ ω ╥)\n");
		exit(1);
	}
}

void	init_textures(t_game *game)
{
	load_texture(game, &game->textures[0], game->map.config.north);
	load_texture(game, &game->textures[1], game->map.config.south);
	load_texture(game, &game->textures[2], game->map.config.west);
	load_texture(game, &game->textures[3], game->map.config.east);
}

int	get_texture_pixel(t_data *data, int tex_x, int tex_y)
{
	char	*src;

	src = data->addr + (tex_y * data->line_length + tex_x * (data->bpp / 8));
	return (*(unsigned int *)src);
}

static int get_texture_id(int side, double ray_dx, double ray_dy)
{
    int tex_id;

    if (side == 0) 
    {
        if (ray_dx > 0)
            tex_id = 3; 
        else
            tex_id = 2; 
    }
    else
    {
        if (ray_dy > 0)
            tex_id = 1; 
        else
            tex_id = 0; 
    }
    return (tex_id);
}

void    get_tex_x_id(t_game *g, t_wall_info *info, int *tex_id, int *tex_x)
{
    double  wall_x;

    *tex_id = get_texture_id(info->side, info->ray_dx, info->ray_dy);
    if (info->side == 0)
        wall_x = g->player.y + info->dist * info->ray_dy;
    else
        wall_x = g->player.x + info->dist * info->ray_dx;
    wall_x -= floor(wall_x);
    *tex_x = (int)(wall_x * (double)g->textures[*tex_id].width);
    if (info->side == 0 && info->ray_dx > 0)
        *tex_x = g->textures[*tex_id].width - *tex_x - 1;
    if (info->side == 1 && info->ray_dy < 0)
        *tex_x = g->textures[*tex_id].width - *tex_x - 1;
    info->tex_x = *tex_x;
}
