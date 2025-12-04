/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zetsu <zetsu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:11:13 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/04 02:12:56 by zetsu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**add_line_in_tab(char **tab, int size, char *line)
{
	char	**new_tab;
	int		i;

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
		remove_newline_at_end(line);
		if (is_texture_line(line) && parse_texture_line(line, config))
			config_count++;
		else if (is_color_line(line) && parse_color_line(line, config))
			config_count++;
		else if (ft_strncmp(line, "\n", 1) != 0)
		{
			printf("Error: Invalid line in configuration file\n");
			free(line);
			exit(1);
		}
		free(line);
		if (config_count < 6)
			line = get_next_line(fd);
		else
			return ;
	}
}

void	remove_newline_at_end(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
		i++;
	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = '\0';
}

static void	process_map_line(char *line, t_map *map)
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
	map->data = add_line_in_tab(map->data, map->height, line);
	if (len > map->width)
		map->width = len;
	map->height++;
}

void	read_map_lines(int fd, t_map *map)
{
	char *line;
	int map_started;

	init_map(map, &map_started);
	line = get_next_line(fd);
	while (line)
	{
		remove_newline_at_end(line);
		if (!map_started)
		{
			if (is_empty_line(line))
			{
				free(line);
				line = get_next_line(fd);
				continue;
			}
			else
				map_started = 1;
		}
		else
			error_empty_line(line);
		process_map_line(line, map);
		line = get_next_line(fd);
	}
}
