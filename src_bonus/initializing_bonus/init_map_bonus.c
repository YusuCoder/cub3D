/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:05:20 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:56 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*------------------------*/
/*  Set width of the map  */
/*------------------------*/
int	set_map_width(char **map)
{
	int	height;
	int	width;
	int	max_width;

	height = 0;
	max_width = 0;
	while (map[height])
	{
		width = 0;
		while (map[height][width])
			width++;
		if (width > max_width)
			max_width = width;
		height++;
	}
	return (max_width);
}

/*-------------------------*/
/*  Set height of the map  */
/*-------------------------*/
int	set_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

/*-------------------------*/
/*  Initialize map struct  */
/*-------------------------*/
void	init_map(t_data *data)
{
	t_map	*map;

	map = &data->map;
	map->width = set_map_width(map->map2d);
	map->height = set_map_height(map->map2d);
	map->color_ceiling = get_color(data->texture.rgb_cell[0], \
		data->texture.rgb_cell[1], data->texture.rgb_cell[2], 255);
	map->color_floor = get_color(data->texture.rgb_floor[0], \
		data->texture.rgb_floor[1], data->texture.rgb_floor[2], 255);
}
