/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:12:57 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/29 21:23:08 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_file_height_width(t_map *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open_cub_file(filename);
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		free(line);
		map->height++;
		line = get_next_line(fd);
	}
	clode(fd);
	return (map->height);
}

void	parse_map(t_map *map, char *filename)
{
	int		fd;
	int		y;

	fd = open(filename, O_RDONLY);
	map->height = get_file_height_width(fd, &map->width);
	map->data = malloc(sizeof(char *) * (map->height + 1));
	if (!map->data)
		exit(1);
	y = 0;
	while (y < map->height)
	{
		map->data[y] = get_next_line(fd);
		if (!map->data[y])
			exit(1);
		y++;
	}
	map->data[y] = NULL;
	close(fd);
}




