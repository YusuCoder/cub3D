/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_filter_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:49:12 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/24 15:08:54 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_adress_and_exit(char **tex_path, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tex_path[i]);
		i++;
	}
	free(tex_path);
	perror(RED"Error!\n"RESET);
	exit(EXIT_FAILURE);
}

int	get_filtered_length(char **map, int i)
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

void	filter_map(t_data *data)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	while (data->map.temp_map[i][0] == '\n')
		i++;
	length = get_filtered_length(data->map.temp_map, i);
	data->map.map2d = (char **)malloc(sizeof(char *) * (length + 1));
	if (!data->map.map2d)
		free_and_exit(data->map.temp_map, data);
	j = 0;
	while (data->map.temp_map[i])
	{
		if (data->map.temp_map[i][0] != '\n')
		{
			data->map.map2d[j] = ft_strdup(data->map.temp_map[i]);
			if (!data->map.map2d[j])
				free_adress_and_exit(data->map.map2d, j);
			j++;
		}
		i++;
	}
	data->map.map2d[j] = NULL;
}
