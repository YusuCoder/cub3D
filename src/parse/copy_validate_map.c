/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_validate_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:25:24 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/15 19:45:12 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
		if (map[i][0] != '1')
			return (1);
		while (map[i][j + 1] != '\n')
			j++;
		if (map[i][j] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	middle_walls(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' && ft_strchr(" \t", map[i][j + 1]) != NULL)
				|| (map[i][j] == '0' && ft_strchr(" \t", map[i][j - 1]) != NULL))
				return (1);
			if ((map[i][j] == '0' && ft_strchr(" \t", map[i - 1][j]) != NULL)
				|| (map[i][j] == ' ' && ft_strchr(" \t", map[i + 1][j]) != NULL))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int size_of_lines(char **map)
{
	int i;
	int len;
	int next_len;
	int len_below;

	i = 0;
	while (map[i + 1])
	{
		len = 0;
		next_len = 0;
		len_below = 0;
		while (map[i][len] && map[i][len] != '\n')
			len++;
		while (map[i + 1][next_len] && map[i + 1][next_len] != '\n')
			next_len++;
		if (map[i + 2])
		{
			while (map[i + 1][len_below] && map[i + 2][len_below] != '\n')
				len_below++;
		}
		if (next_len > len)
		{
			while(map[i + 1][len] && map[i + 1][len] != '\n')
			{
				if (map[i + 1][len] == '0')
					return (1);
				len++;
			}
		}
		if (map[i + 2] && next_len > len_below)
		{
			while (map[i + 1][len_below] && map[i + 1][len_below] != '\n')
			{
				if (map[i + 1][len_below] == '0')
					return (1);
				len_below++;
			}
		}
		i++;
	}
	return (0);
}


void	check_walls(t_data *data)
{
	if (top_and_btm_walls(data->map.map2d) == 1)
	{
		printf("Map is not covered with walls\n");
		free_and_exit(data->map.map2d);
	}
	if (side_walls(data->map.map2d) == 1)
	{
		printf("Map is not covered with walls\n");
		free_and_exit(data->map.map2d);
	}
	if (middle_walls(data->map.map2d) == 1)
	{
		printf("Map is not covered with walls\n");
		free_and_exit(data->map.map2d);
	}
	if (size_of_lines(data->map.map2d) == 1)
	{
		printf("Map is not covered with walls\n");
		free_and_exit(data->map.map2d);
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
