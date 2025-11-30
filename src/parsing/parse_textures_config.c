/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:00:54 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/30 15:28:43 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_texture_identifier(char *line, int *i)
{
	if (!line || !i)
		return (0);
	if ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'))
	{
		*i = 2;
		return (1);
	}
	return (0);
}


static int	get_texture_index(char *line, int *i)
{
	if (!line || !i)
	{
		printf("Error\nNull line or index pointer\n");
		return (0);
	}
	if (!check_texture_identifier(line, i))
		return (0);
	if (line[*i] != ' ')
	{
		printf("Error\nMissing space after identifier\n");
		return (0);
	}
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\0')
	{
		printf("Error\nMissing texture path\n");
		return (0);
	}
	return (1);
}

static int	store_texture_path(char *line, int i, t_config *config)
{
	if (!line || !config)
		return (0);
	if (line[0] == 'N' && line[1] == 'O')
		config->north = ft_strdup(line + i);
	else if (line[0] == 'S' && line[1] == 'O')
		config->south = ft_strdup(line + i);
	else if (line[0] == 'W' && line[1] == 'E')
		config->west = ft_strdup(line + i);
	else if (line[0] == 'E' && line[1] == 'A')
		config->east = ft_strdup(line + i);
	if ((line[0] == 'N' && line[1] == 'O' && !config->north)
		|| (line[0] == 'S' && line[1] == 'O' && !config->south)
		|| (line[0] == 'W' && line[1] == 'E' && !config->west)
		|| (line[0] == 'E' && line[1] == 'A' && !config->east))
	{
		printf("Error\nFailed to allocate texture path\n");
		return (0);
	}
	return (1);
}

int	parse_texture_line(char *line, t_config *config)
{
	int	i;

	if (!get_texture_index(line, &i))
		return (0);
	if (!store_texture_path(line, i, config))
		return (0);
	return (1);
}

