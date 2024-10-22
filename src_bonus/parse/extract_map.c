/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:10:56 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/22 12:49:30 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	get_length(char **map, int i)
{
	int	temp;

	temp = i;
	while (map[i])
		i++;
	if (temp > 0)
		i -= temp;
	return(i);
}

int get_filtered_length(char **map, int i)
{
    int count;

	count = 0;
    while (map[i])
    {
        if (map[i][0] != '\n')
            count++;
        i++;
    }

    return (count);
}

void	extract_map(t_data *data)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	length = 0;
	while (data->map.map_file[i])
	{
		if (i > 0 && data->map.map_file[i - 1][0] == 'C')
		{
			length = get_length(data->map.map_file, i);
			data->map.temp_map = (char **)malloc(sizeof(char *) * (length + 1));
			if (!data->map.temp_map)
				free_and_exit(data->map.map_file, data);
			j = 0;
			while (data->map.map_file[i])
			{
				data->map.temp_map[j] = ft_strdup(data->map.map_file[i]);
				if (!data->map.temp_map[j])
				{
					while (--j >= 0)
						free(data->map.temp_map[j]);
					free(data->map.temp_map);
					exit(EXIT_FAILURE);
				}
				j++;
				i++;
			}
			data->map.temp_map[j] = NULL;
			break;
		}
		i++;
	}
}
void filter_map(t_data *data)
{
    int i;
    int j;
    int length;

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
            {
                while (--j >= 0)
                    free(data->map.map2d[j]);
                free(data->map.map2d);
				free_map(data->map.temp_map);
                exit(EXIT_FAILURE);
            }
            j++;
        }
        i++;
    }
    data->map.map2d[j] = NULL;
}
