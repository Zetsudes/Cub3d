/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:38 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/12/09 08:43:58 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);
	ft_bzero(&game, sizeof(t_game));
	parse_map(&game.map, av[1]);
	verify_map_copy(&game.map);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D Test");
	game.img.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp,
			&game.img.line_length, &game.img.endian);
	init_textures(&game);
	init_player(&game.player, &game.map);
	cast_all_rays(&game.player, &game.map, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	free_config(&game.map.config);
	return (0);
}
