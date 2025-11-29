/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:43:54 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/29 22:51:50 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_atoi_color(char *str, int *i)
{
	int	rgb;

	rgb = 0;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		rgb = rgb * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (str[*i] == ',')
		(*i)++;
	return (rgb);
}

static int	parse_rgb_values(char *line, int *r, int *g, int *b)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	*r = ft_atoi_color(line, &i);
	*g = ft_atoi_color(line, &i);
	*b = ft_atoi_color(line, &i);

	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		printf("Error\nInvalid color values: %d,%d,%d\n", *r, *g, *b);
		return (0);
	}
	return (1);
}

static int	assign_color(char identifier, int r, int g, int b, t_config *config)
{
	if (identifier == 'F')
	{
		config->floor[0] = r;
		config->floor[1] = g;
		config->floor[2] = b;
	}
	else if (identifier == 'C')
	{
		config->ceiling[0] = r;
		config->ceiling[1] = g;
		config->ceiling[2] = b;
	}
	else
	{
		printf("Error\nInvalid color identifier: %c\n", identifier);
		return (0);
	}
	return (1);
}

int	parse_color_line(char *line, t_config *config)
{
	int	r, g, b;

	if (!parse_rgb_values(line, &r, &g, &b))
		return (0);
	return (assign_color(line[0], r, g, b, config));
}




