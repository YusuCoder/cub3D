/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/23 21:11:20 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	radian(int degree)
{
	double	result;

	result = degree * (M_PI / 180);
	return (result);
}

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

void	action_handling(t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, cos(player->pov) * MOVE, sin(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -cos(player->pov) * MOVE, -sin(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, sin(player->pov) * MOVE, -cos(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, -sin(player->pov) * MOVE, cos(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.pov -= ROTATE;
		if (data->player.pov < 0)
			data->player.pov += radian(360);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.pov += ROTATE;
		if (data->player.pov > radian(360))
			data->player.pov -= radian(360);
	}
}

void	simulation(void *param)
{
	t_data *data;

	data = param;
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	action_handling(data);
	ray_casting(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error_free_exit(data, "Failed to display mlx image");
}
