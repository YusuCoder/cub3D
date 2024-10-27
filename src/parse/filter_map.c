/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:44:23 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/27 17:14:09 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	get_filtered_length(char **map, int i)
{
	int	count;

	count = 0;
	while (map[i])
	{
		if (map[i][0] != '\n')
			count++;
		i++;
	}
	return (count);
}

static int	find_first_non_empty_line(char **temp_map)
{
	int	i;

	i = 0;
	while (temp_map[i] && temp_map[i][0] == '\n')
		i++;
	return (i);
}

static char	**copy_filtered_map(char **temp_map, int start_index, int length)
{
	char	**map2d;
	int		j;

	j = 0;
	map2d = (char **)malloc(sizeof(char *) * (length + 1));
	if (!map2d)
		return (NULL);
	while (temp_map[start_index])
	{
		if (temp_map[start_index][0] != '\n')
		{
			map2d[j] = ft_strdup(temp_map[start_index]);
			if (!map2d[j])
			{
				while (--j >= 0)
					free(map2d[j]);
				free(map2d);
				return (NULL);
			}
			j++;
		}
		start_index++;
	}
	map2d[j] = NULL;
	return (map2d);
}

int	pre_check_map(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				flag++;
			j++;
		}
		i++;
	}
	if (flag < 2)
		return (0);
	return (1);
}

void	filter_map(t_data *data)
{
	int	start_index;
	int	length;

	if (pre_check_map(data->map.temp_map) == 0)
	{
		free_map(data->texture.tex_path);
		free_map(data->texture.rgb_codes);
		free_map(data->map.temp_map);
		printf(RED"Invalid Map!\n"RESET);
		exit(EXIT_FAILURE);
	}
	start_index = find_first_non_empty_line(data->map.temp_map);
	length = get_filtered_length(data->map.temp_map, start_index);
	data->map.map2d = copy_filtered_map(data->map.temp_map, \
		start_index, length);
	if (!data->map.map2d)
		free_and_exit(data->map.temp_map, data);
}
