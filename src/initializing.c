/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:25:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/26 21:04:36 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	if (!texture->north || !texture->south
		|| !texture->east || !texture->west)
		error_free_exit(data, "Failed to create mlx texture");
}

void	invert_view(t_player *player)
{
	if (player->pov == NORTH)
		player->angle = radian(270);
	else if (player->pov == SOUTH)
		player->angle = radian(90);
	else if (player->pov == EAST)
		player->angle = radian(0);
	else if (player->pov == WEST)
		player->angle = radian(180);
}

void	init_player(t_data *data)
{
	t_player	*player;
	t_map		*map;

	player = &data->player;
	map = &data->map;
	player->fov = radian(VIEW);
	player->pos.x = map->player_position.x + 0.5;
	player->pos.y = map->player_position.y + 0.5;
	if (map->player_direction == 'N')
		player->pov = NORTH;
	else if (map->player_direction == 'S')
		player->pov = SOUTH;
	else if (map->player_direction == 'E')
		player->pov = EAST;
	else if (map->player_direction == 'W')
		player->pov = WEST;
	invert_view(player);
}

void	init_map(t_data *data)
{
	t_map	*map;

	map = &data->map;
	map->color_ceiling = get_color(data->texture.rgb_cell[0], \
		data->texture.rgb_cell[1], data->texture.rgb_cell[2], 255);
	map->color_floor = get_color(data->texture.rgb_floor[0], \
		data->texture.rgb_floor[1], data->texture.rgb_floor[2], 255);
}

void	init_data(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->buf = NULL;
	data->texture.east = NULL;
	data->texture.west = NULL;
	data->texture.north = NULL;
	data->texture.south = NULL;
	data->img = NULL;
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	if (data->mlx == NULL)
		error_free_exit(data, "Failed to create mlx");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	init_map(data);
	init_player(data);
	init_texture(data);
}
