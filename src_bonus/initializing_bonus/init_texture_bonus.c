/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:09:23 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/16 10:40:20 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

bool	check_door(mlx_texture_t *door[], int limit)
{
	int	i;

	i = 0;
	while (i <= limit)
	{
		if (door[i] == NULL)
			return (false);
		i++;
	}
	return (true);
}

void	init_texture(t_data *data)
{
	t_texture	*texture;
	t_map		*map;

	texture = &data->texture;
	map = &data->map;
	texture->ceiling = map->color_ceiling;
	texture->floor = map->color_floor;
	texture->north = mlx_load_png(map->path_texture_north);
	texture->south = mlx_load_png(map->path_texture_south);
	texture->east = mlx_load_png(map->path_texture_east);
	texture->west = mlx_load_png(map->path_texture_west);
	texture->door_left[0] = mlx_load_png("textures/door/door_left_1.png");
	texture->door_left[1] = mlx_load_png("textures/door/door_left_2.png");
	texture->door_left[2] = mlx_load_png("textures/door/door_left_3.png");
	texture->door_left[3] = mlx_load_png("textures/door/door_left_4.png");
	texture->door_left[4] = mlx_load_png("textures/door/door_left_full.png");
	texture->door_right[0] = mlx_load_png("textures/door/door_right_1.png");
	texture->door_right[1] = mlx_load_png("textures/door/door_right_2.png");
	texture->door_right[2] = mlx_load_png("textures/door/door_right_3.png");
	texture->door_right[3] = mlx_load_png("textures/door/door_right_4.png");
	texture->door_right[4] = mlx_load_png("textures/door/door_right_full.png");
	if (!texture->north || !texture->south || !texture->east || !texture->west \
		|| !check_door(texture->door_left, 5)
		|| !check_door(texture->door_right, 5))
		error_free_exit(data, "Failed to create mlx texture");
	texture->test = mlx_load_png("textures/wall/wood1.png");
}
