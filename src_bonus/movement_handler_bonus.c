/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:13 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/26 14:39:01 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*----------------------------*/
/*  Define player's movement  */
/*----------------------------*/
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
	if ((tile_y != '1' && tile_y != '2')
		&& (tile_x != '1' && tile_x != '2')
		&& (tile_diag != '1' && tile_diag != '2'))
	{
		player->pos.y = new.y;
		player->pos.x = new.x;
	}
	else if ((tile_y != '1' && tile_y != '2') && move_y != 0)
		player->pos.y = new.y;
	else if ((tile_x != '1' && tile_x != '2') && move_x != 0)
		player->pos.x = new.x;
}

/*-------------------------*/
/*  Handle mouse movement  */
/*-------------------------*/
void	movement_mouse(t_data *data)
{
	double			*angle;
	t_point_int		pos;
	t_point_double	delta;

	angle = &data->player.angle;
	mlx_get_mouse_pos(data->mlx, &pos.x, &pos.y);
	delta.x = pos.x - (data->width / 2);
	*angle += delta.x * MOUSE_SPEED;
	if (*angle < 0)
		*angle += radian(360);
	else if (*angle > radian(360))
		*angle -= radian(360);
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}

/*----------------------------*/
/*  Handle player's movement  */
/*----------------------------*/
void	check_sound(t_data *data, bool is_moving)
{
	if (is_moving)
	{
		if (data->sound_pid <= 0)
			data->sound_pid = player_move_sound();
	}
	else
	{
		if (data->sound_pid > 0)
		{
			kill(data->sound_pid, SIGKILL);
			data->sound_pid = -1;
		}
	}
}

bool	move_hooks(t_data *data, bool is_moving, double *angle)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		move_player(data, cos(*angle) * MOVE, sin(*angle) * MOVE);
		is_moving = true;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		move_player(data, -cos(*angle) * MOVE, -sin(*angle) * MOVE);
		is_moving = true;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		move_player(data, sin(*angle) * MOVE, -cos(*angle) * MOVE);
		is_moving = true;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		move_player(data, -sin(*angle) * MOVE, cos(*angle) * MOVE);
		is_moving = true;
	}
	return (is_moving);
}

void	movement_handler(t_data *data)
{
	double	*angle;
	bool	is_moving;

	is_moving = false;
	angle = &data->player.angle;
	is_moving = move_hooks(data, is_moving, angle);
	check_sound(data, is_moving);
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
	movement_mouse(data);
}
