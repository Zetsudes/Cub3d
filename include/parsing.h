/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:11:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/02 16:18:22 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_config
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			floor[3];
	int			ceiling[3];
}				t_config;

typedef struct s_map
{
	char		**data;
	int			width;
	int			height;
	t_pos		player_start;
	char		player_start_dir;
	t_config	config;
}				t_map;

// parse.c
void			parse_map(t_map *map, char *filename);

// read_map.c
void			read_config_lines(int fd, t_config *config);
void			read_map_lines(int fd, t_map *map);

// parse_file.c
int				open_cub_file(char *filename);

// parse_map.c
void			verify_map_copy(t_map *map);

// parse_utils.c
char			**map_copy(char **map_copy);
int				is_traversable(char c);
int				is_filled_or_wall(char c);
void			check_valid_char(char c);

// parse_config.c
int				is_texture_line(char *line);
int				is_color_line(char *line);

// parse_textures_config.c
int				parse_texture_line(char *line, t_config *config);
void			free_config(t_config *config);

// parse_colors_config.c
int				parse_color_line(char *line, t_config *config);

#endif
