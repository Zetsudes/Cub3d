/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:32:05 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/03 16:41:43 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_map(t_map *map, int *map_started)
{
	*map_started = 0;
	map->data = NULL;
	map->height = 0;
	map->width = 0;
}

void	error_empty_line(char *line)
{
	if (is_empty_line(line))
	{
		printf("Error: empty line inside the map\n");
		free(line);
		exit(1);
	}
}

