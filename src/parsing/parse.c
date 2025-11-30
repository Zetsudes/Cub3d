/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:12:57 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/30 16:08:37 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	read_config_lines(int fd, t_config *config)
{
	int		config_count;
	char	*line;

	config_count = 0;
	line = get_next_line(fd);
	while (line && config_count < 6)
	{
		if (is_texture_line(line) &&
			parse_texture_line(line, config))
				config_count++;
		else if (is_color_line(line) &&
			parse_color_line(line, config))
				config_count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

static int	get_map_height_width(t_map *map, int fd)
{
	char *line;

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
	return (map->height);
}

void	parse_map(t_map *map, char *filename)
{
	int		fd;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	read_config_lines(fd, &map->config);
	map->height = get_map_height_width(map, fd);
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





