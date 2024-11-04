/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_extract_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:10:56 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/27 16:53:09 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	get_length(char **map, int i)
{
	int	temp;

	temp = i;
	while (map[i])
		i++;
	if (temp > 0)
		i -= temp;
	return (i);
}

static int	find_map_start(char **map_file)
{
	int	i;

	i = 0;
	while (map_file[i])
	{
		if (i > 0 && map_file[i - 1][0] == 'C')
			return (i);
		i++;
	}
	return (-1);
}

static char	**allocate_temp_map(char **map_file, int start_index, int length)
{
	char	**temp_map;
	int		i;

	temp_map = (char **)malloc(sizeof(char *) * (length + 1));
	if (!temp_map)
		return (NULL);
	i = 0;
	while (map_file[start_index] && i < length)
	{
		temp_map[i] = ft_strdup(map_file[start_index]);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			return (NULL);
		}
		start_index++;
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

void	extract_map(t_data *data)
{
	int	start_index;
	int	length;

	start_index = find_map_start(data->map.map_file);
	if (start_index == -1)
	{
		free_map(data->texture.rgb_codes);
		free_map(data->texture.tex_path);
		free_map(data->map.map_file);
		printf(RED"No map found!\n"RESET);
		exit(EXIT_FAILURE);
	}
	length = get_length(data->map.map_file, start_index);
	data->map.temp_map = allocate_temp_map(data->map.map_file, \
			start_index, length);
	if (!data->map.temp_map)
		free_and_exit(data->map.map_file, data);
}
