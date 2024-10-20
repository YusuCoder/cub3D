/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:09:23 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/20 16:14:17 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*-----------------------------*/
/*  Initialize texture struct  */
/*-----------------------------*/
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
	texture->door = mlx_load_png("textures/wall/wood1.png");
	if (!texture->north
		|| !texture->south
		|| !texture->east
		|| !texture->west
		|| !texture->door)
		error_free_exit(data, "Failed to create mlx texture");
}
