#include "parsing.h"

int	is_texture_line(char *line)
{
	if (!line)
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	if (!ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3))
		return (1);
	if (!ft_strncmp(line, "EA ", 3))
		return (1);
	return (0);
}

int	is_color_line(char *line)
{
	if (line[0] == 'F')
		return (1);
	if (line[0] == 'C')
		return (1);
	return (0);
}

void	free_config(t_config *config)
{
	if (!config)
	{
		printf("Error\nfree_config called with NULL pointer\n");
		return ;
	}
	free(config->north);
	free(config->south);
	free(config->west);
	free(config->east);
}

