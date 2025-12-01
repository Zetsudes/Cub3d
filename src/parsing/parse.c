/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:12:57 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/01 17:11:23 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
