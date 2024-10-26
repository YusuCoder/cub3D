/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/26 14:42:07 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(t_data *data, double move_x, double move_y)
{
	t_player		*player;
	t_point_double	new;
	char			tile_x;
	char			tile_y;
	char			tile_diag;

	player = &data->player;
	new.x = player->pos.x + move_x;
	new.y = player->pos.y + move_y;
	tile_x = get_tile_x(&data->map, new, player, move_x);
	tile_y = get_tile_y(&data->map, new, player, move_y);
	tile_diag = get_tile_diag(&data->map, new, move_x, move_y);
	if ((tile_y != '1')
		&& (tile_x != '1')
		&& (tile_diag != '1'))
	{
		player->pos.y = new.y;
		player->pos.x = new.x;
	}
	else if (tile_y != '1' && move_y != 0)
		player->pos.y = new.y;
	else if (tile_x != '1' && move_x != 0)
		player->pos.x = new.x;
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
	t_data	*data;

	data = param;
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	movement_hook(data);
	ray_casting(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error_free_exit(data, "Failed to display mlx image");
}
