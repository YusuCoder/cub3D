/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_contents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:51:43 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/19 16:09:42 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	bottom_top_walls(char **map, int i, int j)
{
	if (!map || !map[i] || !map[i][j])
		return (1);
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r' || map[i][j] == '\v' || map[i][j] == '\f')
	{
		if (map[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

void	side_walls(t_map *data, char **map)
{
	int	i;
	int	j;

	if (bottom_top_walls(map, 0, 0) == 1)
		exit(EXIT_FAILURE);
	i = 1;
	while (i < (data->height - 1))
	{
		j = ft_strlen(map[i]) - 1;
		if (map[i][j] != '1')
			exit(EXIT_FAILURE);
		i++;
	}
	if (bottom_top_walls(map, i, 0) == 1)
		exit(EXIT_FAILURE);
}

void	check_map_contents(t_data *data, char **map)
{
	if (data->map_info.map == NULL)
		exit(EXIT_FAILURE);
	// printf("%d\n", data->map_info.width);
	side_walls(&data->map_info, map);
}
