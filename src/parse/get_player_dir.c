/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:44 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/20 16:25:54 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_player(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j] != '\n')
		{
			if (ft_strchr("NEWS", map[i][j]) != NULL)
			{
				data->map.player_direction = map[i][j];
				data->map.player_position.x = j;
				data->map.player_position.y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player_pos(char **map)
{
	int	i;
	int	k;

	i = 1;
	while (map && map[i + 2])
	{
		k = 0;
		while (map[i][k])
		{
			if ((ft_strchr("NEWS", map[i][k]) != NULL && ft_strchr(" \t", map[i][k + 1]) != NULL)
					|| (ft_strchr("NEWS", map[i][k]) != NULL && ft_strchr(" \t", map[i][k - 1]) != NULL))
				return (1);
			if ((ft_strchr("NEWS", map[i][k]) != NULL && ft_strchr(" \t", map[i + 1][k]) != NULL)
					|| (ft_strchr("NEWS", map[i][k]) != NULL && ft_strchr(" \t", map[i - 1][k]) != NULL))
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

void	get_player_dir(t_data *data)
{
	if(check_player(data->map.map2d, data) == 1)
	{
		printf("No player found!\n");
		free_and_exit(data->map.map2d);
	}
	if (check_player_pos(data->map.map2d) == 1)
	{
		printf("Warning! Player is in a danger zone!\n");
		free_and_exit(data->map.map2d);
	}
}
