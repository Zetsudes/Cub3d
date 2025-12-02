/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:11:00 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/12/02 16:16:22 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int is_cub_file(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if(ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

int open_cub_file(char *filename)
{
	int fd;
	fd = open(filename, O_RDONLY);

	if (!is_cub_file(filename))
	{
		printf("Error: Invalid file extension (expected .cub)\n");
		exit (-1);
	}
	if (fd < 0)
	{
		printf("Error: Cannot open .cub file\n");
		exit (-1);
	}
	return (fd);
}
