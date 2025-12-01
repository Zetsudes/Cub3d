/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:11:13 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/01 17:12:04 by pmeimoun         ###   ########.fr       */
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

void	read_config_lines(int fd, t_config *config)
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

static void	remove_newline(char *line)
{
	int i = 0;

	if (!line)
		return ;
	while (line[i])
		i++;
	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = '\0';
}

static void	process_map_line(char *line, t_map *map, int size)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		check_valid_char(line[i]);
		i++;
	}
	map->data = add_line_in_tab(map->data, size, line);
	if (len > map->width)
		map->width = len;
	map->height++;
}

void	read_map_lines(int fd, t_map *map)
{
	char	*line;
	int		size;

	map->data = NULL;
	map->height = 0;
	map->width = 0;
	size = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (*line != '\n' && *line != '\0')
		{
			process_map_line(line, map, size);
			size++;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
}