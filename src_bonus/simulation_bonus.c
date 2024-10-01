/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/01 19:17:38 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

// void	move_player(t_data *data, double move_column, double move_row)
// {
// 	t_map		*map;
// 	t_player	*player;
// 	double		column;
// 	double		row;

// 	map = &data->map;
// 	player = &data->player;
// 	column = player->pos.x + move_column;
// 	row = player->pos.y + move_row;
// 	if (map->map2d[(int)row][(int)player->pos.x] != '1')
// 		player->pos.y = row;
// 	if (map->map2d[(int)player->pos.y][(int)column] != '1')
// 		player->pos.x = column;
// }

void	move_player(t_data *data, double move_x, double move_y)
{
	t_map		*map;
	t_player	*player;
	double		new_x;
	double		new_y;
	int			tile_x;
	int			tile_y;

	map = &data->map;
	player = &data->player;

	// Calculate new intended position
	new_x = player->pos.x + move_x;
	new_y = player->pos.y + move_y;

	// Check the map for collision at the new position
	tile_x = (int)new_x;
	tile_y = (int)new_y;

	// Ensure the player moves only if the new position is within an empty space ('0')
	if (map->map2d[tile_y][(int)player->pos.x] != '1')
		player->pos.y = new_y;
	if (map->map2d[(int)player->pos.y][tile_x] != '1')
		player->pos.x = new_x;
}

void	movement_hook(t_data *data)
{
	double	*angle;

	angle = &data->player.angle;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, cos(*angle) * MOVE, sin(*angle) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -cos(*angle) * MOVE, -sin(*angle) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, sin(*angle) * MOVE, -cos(*angle) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, -sin(*angle) * MOVE, cos(*angle) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		*angle -= ROTATE;
		if (*angle < 0)
			*angle += radian(360);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		*angle += ROTATE;
		if (*angle > radian(360))
			*angle -= radian(360);
	}
}

void	simulation(void *param)
{
	t_data		*data;
	t_sprite	*sprite;

	data = param;
	sprite = &data->sprite;
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	movement_hook(data);
	ray_casting(data);
	draw_minimap(data);
	draw_sprite(data->img, sprite->aim, \
		data->img->width / 2 - sprite->aim->width / 2, \
		data->img->height / 2 - sprite->aim->height / 2);
	draw_sprite(data->img, sprite->rifle, \
		data->img->width / 2 + (data->img->width / 2 - sprite->rifle->width), \
		data->img->height / 2 + (data->img->height / 2 - sprite->rifle->height));
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error_free_exit(data, "Failed to display mlx image");
}
