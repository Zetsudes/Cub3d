/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:29:31 by zamohame          #+#    #+#             */
/*   Updated: 2025/10/30 14:22:07 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(void)
{
	void	*mlx;
	void	*win;
	t_data	img;
	int		y;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "wassup");
	y = 0;
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	while (y < 600)
	{
		my_mlx_pixel_put(&img, 400, y, 0xFF0000);
		y++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
