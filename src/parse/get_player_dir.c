/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:44 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/16 15:59:25 by ryusupov         ###   ########.fr       */
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

void	get_player_dir(t_data *data)
{
	if(check_player(data->map.map2d, data) == 1)
	{
		printf("No player found!\n");
		free_and_exit(data->map.map2d);
	}
}
