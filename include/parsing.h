/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:11:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/30 15:45:30 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;

typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
	t_pos	player_start;
	char 	player_start_dir;
} t_map;

typedef struct s_config {
	char *north;
	char *south;
	char *west;
	char *east;
	int floor[3];
	int ceiling[3];
} t_config;

// parse.c
void	parse_map(t_map *map, char *filename, t_config *config);

// parse_file.c
int			open_cub_file(char *filename);

// parse_map.c
void		verify_map_copy(char **map_copy, int player_x, int player_y, int width, int height);

// parse_utils.c
char		**map_copy(char **map_copy);
int			is_traversable(char c);
int			is_filled_or_wall(char c);
void		check_valid_char(char c);

// parse_config.c
int			is_texture_line(char *line);
int			is_color_line(char *line);

// parse_textures_config.c
int			parse_texture_line(char *line, t_config *config);

// parse_colors_config.c
int			parse_color_line(char *line, t_config *config);

#endif
