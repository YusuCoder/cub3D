/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:25:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/13 13:52:40 by ryusupov         ###   ########.fr       */
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
		player->angle = radian(180);
	else if (player->pov == WEST)
		player->angle = radian(0);
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
	map->map2d = (char **)malloc(10 * sizeof(char *));
	if (map->map2d == NULL)
		error_free_exit(data, "malloc");
	map->map2d[0] = ft_strdup(" 1111111111111111111111111111111111111111111 ");
	map->map2d[1] = ft_strdup("100001000000000000000010000000000000010000001");
	map->map2d[2] = ft_strdup("100001000000000000000010000000000000010000001");
	map->map2d[3] = ft_strdup("100001000000000000000010000000000000010000001");
	map->map2d[4] = ft_strdup("100000000001111111111110000000000000000000001");
	map->map2d[5] = ft_strdup("100000000000000000000000000000011111111111111");
	map->map2d[6] = ft_strdup("100000000000000000000000000000000000000000001");
	map->map2d[7] = ft_strdup("1000N0000000000000000000000000000000000000001");
	map->map2d[8] = ft_strdup(" 1111111111111111111111111111111111111111111 ");
	map->map2d[9] = NULL;
	map->player_direction = 'N';
	map->player_position.x = 4;
	map->player_position.y = 7;
	map->color_ceiling = get_color(data->texture.rgb_cell[0], data->texture.rgb_cell[1], data->texture.rgb_cell[2], 255);
	map->color_floor = get_color(data->texture.rgb_floor[0], data->texture.rgb_floor[1], data->texture.rgb_floor[2], 255);
	// map->path_texture_north = "textures/wall/metal1.png";
	// map->path_texture_south = "textures/wall/metal2.png";
	// map->path_texture_east = "textures/wall/metal3.png";
	// map->path_texture_west = "textures/wall/rock2.png";
}

void	init_data(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->buf = NULL;
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
