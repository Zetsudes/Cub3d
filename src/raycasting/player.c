/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zetsu <zetsu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:31:36 by zamohame          #+#    #+#             */
/*   Updated: 2025/12/08 14:34:13 by zetsu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void set_dir_vectors(t_player *p, double dx, double dy)
{
    p->dir_x = dx;
    p->dir_y = dy;
}

static void set_plane_vectors(t_player *p, double px, double py)
{
    p->plane_x = px;
    p->plane_y = py;
}

void    init_player(t_player *p, t_map *map)
{
    p->x = (double)map->player_start.x + 0.5;
    p->y = (double)map->player_start.y + 0.5;

    if (map->player_start_dir == 'E')
    {
        set_dir_vectors(p, 1.0, 0.0);       
        set_plane_vectors(p, 0.0, PLANE_LEN); 
    }
    else if (map->player_start_dir == 'W')
    {
        set_dir_vectors(p, -1.0, 0.0);
        set_plane_vectors(p, 0.0, -PLANE_LEN);
    }
    else if (map->player_start_dir == 'N')
    {
        set_dir_vectors(p, 0.0, -1.0);
        set_plane_vectors(p, -PLANE_LEN, 0.0);
    }
    else
    {
        set_dir_vectors(p, 0.0, 1.0);
        set_plane_vectors(p, PLANE_LEN, 0.0);
    }
}

void	rotate_left(t_player *p)
{
	double	old_dx;
	double	old_px;
	double	ang;

	ang = ROT_SPEED;
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos(ang) - p->dir_y * sin(ang);
	p->dir_y = old_dx * sin(ang) + p->dir_y * cos(ang);
	p->plane_x = p->plane_x * cos(ang) - p->plane_y * sin(ang);
	p->plane_y = old_px * sin(ang) + p->plane_y * cos(ang);
}

void	rotate_right(t_player *p)
{
	double	old_dx;
	double	old_px;
	double	ang;

	ang = -ROT_SPEED;
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos(ang) - p->dir_y * sin(ang);
	p->dir_y = old_dx * sin(ang) + p->dir_y * cos(ang);
	p->plane_x = p->plane_x * cos(ang) - p->plane_y * sin(ang);
	p->plane_y = old_px * sin(ang) + p->plane_y * cos(ang);
}
