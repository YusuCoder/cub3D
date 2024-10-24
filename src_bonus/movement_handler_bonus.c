/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:13 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/22 10:41:36 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*----------------------------*/
/*  Define player's movement  */
/*----------------------------*/
void	move_player(t_data *data, double move_x, double move_y)
{
	t_map			*map;
	t_player		*player;
	t_point_double	new;
	char			tile_x;
	char			tile_y;

	map = &data->map;
	player = &data->player;
	new.x = player->pos.x + move_x;
	new.y = player->pos.y + move_y;
	if (new.y > player->pos.y)
		tile_y = map->map2d[(int)(new.y + PADDING)][(int)player->pos.x];
	else
		tile_y = map->map2d[(int)(new.y - PADDING)][(int)player->pos.x];
	if (new.x > player->pos.x)
		tile_x = map->map2d[(int)player->pos.y][(int)(new.x + PADDING)];
	else
		tile_x = map->map2d[(int)player->pos.y][(int)(new.x - PADDING)];
	if (tile_y != '1' && tile_y != '2')
		player->pos.y = new.y;
	if (tile_x != '1' && tile_x != '2')
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
