/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:16:25 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/08 11:45:05 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
