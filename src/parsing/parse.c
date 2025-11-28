/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:12:57 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/11/28 22:39:12 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void parse(char *filename)
{
	int fd;
	char *line;

	fd = open_cub_file(filename);
	while ((line = get_next_line(fd)) != NULL)
	{}
}
