/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:30:30 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/20 14:45:06 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			if (ft_strchr("10NWES\n \t", map[i][j]) == NULL)
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
		free_and_exit(data->map.map2d);
	}
	if (check_all_components(data->map.map2d) == 1)
	{
		printf("Unnecessary component found!\n");
		free_and_exit(data->map.map2d);
	}
}
