/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:25:24 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/12 16:30:36 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	copy_map(int row, int column, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->map.fd);
	while (line != NULL)
	{
		data->map.map_file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map.map_file[row])
			exit(EXIT_FAILURE);
		while (line[i])
		{
			data->map.map_file[row][column++] = line[i++];
		}
		data->map.map_file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(data->map.fd);
	}
	data->map.map_file[row] = NULL;
}
