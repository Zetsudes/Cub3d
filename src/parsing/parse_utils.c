/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:16:25 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/02 16:17:44 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**map_copy_alloc_and_fill(char **map_copy, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map_copy[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**map_copy(char **map_copy)
{
	int	height;

	if (!map_copy)
		return (NULL);
	height = 0;
	while (map_copy[height])
		height++;
	return (map_copy_alloc_and_fill(map_copy, height));
}

int	is_traversable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_filled_or_wall(char c)
{
	return (c == '1' || c == 'F');
}

void	check_valid_char(char c)
{
	if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
			|| c == ' '))
	{
		printf("Error: invalid character in map\n");
		exit(1);
	}
}
