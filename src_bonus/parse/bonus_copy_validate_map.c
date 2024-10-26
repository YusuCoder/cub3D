/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_copy_validate_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:25:24 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/24 14:29:14 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	top_and_btm_walls(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[0][j] != '\n')
	{
		if (ft_strchr("1 \t", map[0][j]) == NULL)
			return (1);
		j++;
	}
	i = 0;
	while (map[i + 1] != NULL)
		i++;
	j = 0;
	while (map[i][j] != '\n')
	{
		if (ft_strchr("1 \t", map[i][j]) == NULL)
			return (1);
		j++;
	}
	return (0);
}

int	side_walls(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i + 2] != NULL)
	{
		j = 0;
		while (ft_strchr(" \t", map[i][j]) != NULL)
			j++;
		if (ft_strchr(" \t", map[i][j]) == NULL && map[i][j] != '1')
			return (1);
		while (map[i][j + 1] != '\n')
			j++;
		if (map[i][j] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	check_walls(t_data *data)
{
	if (top_and_btm_walls(data->map.map2d) == 1)
	{
		printf("Top or bottom walls are not closed\n");
		free_and_exit(data->map.map2d, data);
	}
	if (side_walls(data->map.map2d) == 1)
	{
		printf("Side walls are not closed\n");
		free_and_exit(data->map.map2d, data);
	}
	if (middle_walls(data->map.map2d) == 1)
	{
		printf("Middle walls are not closed\n");
		free_and_exit(data->map.map2d, data);
	}
	if (size_of_lines(data->map.map2d) == 1)
	{
		printf("Map is not covered with walls\n");
		free_and_exit(data->map.map2d, data);
	}
}

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
