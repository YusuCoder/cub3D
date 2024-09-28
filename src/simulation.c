/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/28 19:15:47 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(t_data *data, double move_column, double move_row)
{
	t_map		*map;
	t_player	*player;
	double		column;
	double		row;

	map = &data->map;
	player = &data->player;
	column = player->pos.x + move_column;
	row = player->pos.y + move_row;
	if (map->map2d[(int)row][(int)player->pos.x] != '1')
		player->pos.y = row;
	if (map->map2d[(int)player->pos.y][(int)column] != '1')
		player->pos.x = column;
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
