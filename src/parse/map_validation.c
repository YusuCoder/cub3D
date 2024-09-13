/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:25:06 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/13 16:47:45 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	copy_map(int row, int column, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->map_info.fd);
	while (line != NULL)
	{
		data->map_info.map[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map_info.map[row])
			error_msg(NULL, "Allocation failed!\n", FAIL);
		while (line[i])
		{
			data->map_info.map[row][column++] = line[i++];
		}
		data->map_info.map[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(data->map_info.fd);
	}
	data->map_info.map[row] = NULL;
}

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
	// printf("%d\n", data->map_info.line_count);
	data->map_info.path = file;
	data->map_info.map = ft_calloc(data->map_info.line_count + 1, sizeof(char *));
	if (!data->map_info.map)
		return ;
	data->map_info.fd = open(file, O_RDONLY);
	if (data->map_info.fd < 0)
		error_msg(file, "Open error!\n", FAIL);
	else
		copy_map(row, column, i, data);
}
