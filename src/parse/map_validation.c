/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:25:06 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/13 14:49:56 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	line_count(char *file)
{
	int		fd;
	int		counter;
	char	*line;

	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg(file, "Open failed!\n", FAIL);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			counter++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (counter);
}

void	validate_map(char *file, t_data *data)
{
	int	row;
	int	column;
	int	i;

	i = 0;
	row = 0;
	column = 0;
	data->map_info.line_count = line_count(file);
}
