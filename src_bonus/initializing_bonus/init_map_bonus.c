/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:05:20 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/01 12:41:57 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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

int	set_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

void	init_map(t_data *data)
{
	t_map	*map;

	map = &data->map;
	map->map2d = (char **)malloc(21 * sizeof(char *));
	if (map->map2d == NULL)
		error_free_exit(data, "malloc");
	map->map2d[0] = ft_strdup("      1111111111111111111111111111111 ");
	map->map2d[1] = ft_strdup("     100000000000000001000000000000001");
	map->map2d[2] = ft_strdup("     100000000000000001000000000000001");
	map->map2d[3] = ft_strdup("11111100000000000000001000000000000001");
	map->map2d[4] = ft_strdup("10000000000111111110011000000000000001");
	map->map2d[5] = ft_strdup("100000000000000000000000000000011111111111111");
	map->map2d[6] = ft_strdup("100000000000000000000000000000000010000000001");
	map->map2d[7] = ft_strdup("100000000011111111000000000000000010000000001");
	map->map2d[8] = ft_strdup("100000000000000001000000000000000010000000001");
	map->map2d[9] = ft_strdup("111001111110111111000000000000000000000000001");
	map->map2d[10] = ft_strdup("100000000000000001111100000000000011111101111");
	map->map2d[11] = ft_strdup("100000000000000000010000000000000010000000001");
	map->map2d[12] = ft_strdup("100000000000000000010000000000000000000000001");
	map->map2d[13] = ft_strdup("100000000011111111110000000000000010000000001");
	map->map2d[14] = ft_strdup("10000000000000000001000000000000001111111111 ");
	map->map2d[15] = ft_strdup("10000000000000000001000000000000001");
	map->map2d[16] = ft_strdup("10000000000000000001000000000000001");
	map->map2d[17] = ft_strdup("10000000000000000000000000000000001111111111 ");
	map->map2d[18] = ft_strdup("1000N0000000000000000000000000000000000000001");
	map->map2d[19] = ft_strdup(" 1111111111111111111111111111111111111111111 ");
	map->map2d[20] = NULL;
	map->width = set_map_width(map->map2d);
	map->height = set_map_height(map->map2d);
	map->player_direction = 'N';
	map->player_position.x = 4;
	map->player_position.y = 18;
	map->color_ceiling = 0x87CEEB;
	map->color_floor = 0x6B8E23;
	map->path_texture_north = "textures/wall/metal1.png";
	map->path_texture_south = "textures/wall/metal2.png";
	map->path_texture_east = "textures/wall/metal3.png";
	map->path_texture_west = "textures/wall/rock2.png";
}
