/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:12:57 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/30 19:59:20 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**add_line_in_tab(char **tab, int size, char *line)
{
	char **new_tab;
	int i;

	new_tab = malloc(sizeof(char *) * (size + 2));
	if (!new_tab)
		exit(1);

	i = 0;
	while (i < size)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[size] = line;
	new_tab[size + 1] = NULL;

	if (tab)
		free(tab);
	return (new_tab);
}

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
		if (config_count < 6)
		{
			line = get_next_line(fd);
		}
		else
			return;
	}
}

static void	read_map_lines(int fd, t_map *map)
{
	char *line;
	int size;

	map->data = NULL;
	map->height = 0;
	map->width = 0;
	size = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && *line != '\0')
		{
			map->data = add_line_in_tab(map->data, size, line);
			size++;
			if ((int)ft_strlen(line) > map->width)
				map->width = ft_strlen(line);
			map->height++;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
}

void	parse_map(t_map *map, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	read_config_lines(fd, &map->config);
	map->data = NULL;
	map->height = 0;
	map->width = 0;

	read_map_lines(fd, map);

	close(fd);
}
