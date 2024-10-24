/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_check_components.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:30:30 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/24 14:30:42 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*---------FREE FUNCTIONS---------*/

void	free_path(t_data *data)
{
	if (data->map.path_texture_north != NULL)
	{
		free(data->map.path_texture_north);
		data->map.path_texture_north = NULL;
	}
	if (data->map.path_texture_east != NULL)
	{
		free(data->map.path_texture_east);
		data->map.path_texture_east = NULL;
	}
	if (data->map.path_texture_west != NULL)
	{
		free(data->map.path_texture_west);
		data->map.path_texture_west = NULL;
	}
	if (data->map.path_texture_south != NULL)
	{
		free(data->map.path_texture_south);
		data->map.path_texture_south = NULL;
	}
}

void	free_color(t_data *data)
{
	if (data->texture.rgb_cell)
		free(data->texture.rgb_cell);
	if (data->texture.rgb_floor)
		free(data->texture.rgb_floor);
}
/*-------END OF FREE FUNCTIONS---------*/

int	one_component_check(char **map)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (flag == 0)
					flag = 1;
				else
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_all_components(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (strchr("10NWES2O\n \t", map[i][j]) == NULL)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	check_components(t_data *data)
{
	if (one_component_check(data->map.map2d) == 1)
	{
		printf("More than one component found!\n");
		free_and_exit(data->map.map2d, data);
	}
	if (check_all_components(data->map.map2d) == 1)
	{
		printf("Unnecessary component found!\n");
		free_and_exit(data->map.map2d, data);
	}
}
