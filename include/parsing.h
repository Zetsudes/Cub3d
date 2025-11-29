/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:11:04 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/29 21:34:53 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// parse.c
void		parse_map(t_map *map_copy, char *filename);

// parse_file.c
int			open_cub_file(char *filename);

// parse_map.c
void		verify_map_copy(char **map_copy, int player_x, int player_y, int width, int height);

// parse_utils.c
char		**map_copy(char **map_copy);
int			is_traversable(char c);
int			is_filled_or_wall(char c);
void		check_valid_char(char c);
