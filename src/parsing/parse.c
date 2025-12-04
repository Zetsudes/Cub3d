/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:12:57 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/02 16:28:23 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_map(t_map *map, char *filename)
{
	int	fd;

	fd = open_cub_file(filename);
	if (fd < 0)
		exit(1);
	read_config_lines(fd, &map->config);
	map->data = NULL;
	map->height = 0;
	map->width = 0;
	read_map_lines(fd, map);
	close(fd);
}
