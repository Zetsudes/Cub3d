/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:38 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/29 21:33:19 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/raycasting.h"
#include "../include/parsing.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	if (ac != 2)
		return (1);
	parse_map(&game.map, av[1]);
    t_game  game;
    /*char *map_data[] = {
        "111111",
        "100001",
        "101001",
        "1000P1",
        "111111",
        NULL
    };*/
    /*game.map.data = map_copy(map_data);
    game.map.width = 6;
    game.map.height = 5;
    game.map.player_start.x = 4
    game.map.player_start.y = 3;
    game.map.player_start_dir = 'N';*/
	verify_map(game.map.data, game.map.player_start.x, game.map.player_start.y,
				game.map.witdth, gane.map.height);
    game.mlx = mlx_init();
    if (!game.mlx)
        return (1);
    game.win = mlx_new_window(game.mlx, win_width, win_height, "Cub3D Test");
    game.img.img = mlx_new_image(game.mlx, win_width, win_height);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp,
                                     &game.img.line_length, &game.img.endian);
    init_player(&game.player, &game.map);
    cast_all_rays(&game.player, &game.map, &game.img);
    mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
    setup_hooks(&game);
    mlx_loop(game.mlx);
    return (0);
}
