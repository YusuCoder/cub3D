/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:36:56 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/20 16:14:49 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*-----------------------------------------------------------------*/
/*  Handle program exiting while clicking the window close button  */
/*-----------------------------------------------------------------*/
void	close_hook(void *param)
{
	t_data	*data;

	data = param;
	free_exit(data, EXIT_SUCCESS);
}

/*-----------------------------------------*/
/*  Handle resizing of the program window  */
/*-----------------------------------------*/
void	resize_hook(int32_t new_width, int32_t new_height, void *param)
{
	t_data	*data;

	data = param;
	if (new_width >= MIN_WIDTH && new_height >= MIN_HEIGHT)
	{
		data->buf = mlx_new_image(data->mlx, new_width, new_height);
		if (data->buf == NULL)
			error_free_exit(data, "Failed to create mlx image");
		data->width = new_width;
		data->height = new_height;
		mlx_delete_image(data->mlx, data->img);
		data->img = data->buf;
		data->buf = NULL;
	}
}

/*-----------------------------*/
/*  Handle minimap definition  */
/*-----------------------------*/
void	handle_minimap(t_data *data)
{
	if (data->is_minimap == true)
		data->is_minimap = false;
	else
		data->is_minimap = true;
}

/*--------------------------*/
/*  Handle door definition  */
/*--------------------------*/
void	handle_door(t_data *data)
{
	t_map		*map;
	t_door		*door;
	t_point_int	pos_door;
	t_point_int	pos_player;

	map = &data->map;
	door = &data->door;
	pos_door.x = door->pos.x;
	pos_door.y = door->pos.y;
	pos_player.x = (int)data->player.pos.x;
	pos_player.y = (int)data->player.pos.y;
	if (door->is_close == true
		&& map->map2d[pos_door.y][pos_door.x] == '2')
		map->map2d[pos_door.y][pos_door.x] = 'O';
	else if (door->is_close == true
		&& map->map2d[pos_door.y][pos_door.x] == 'O'
		&& map->map2d[pos_player.y][pos_player.x] != 'O')
		map->map2d[pos_door.y][pos_door.x] = '2';
}

/*----------------------------------------*/
/*  Handle pushing buttons on a keyboard  */
/*----------------------------------------*/
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		free_exit(data, EXIT_SUCCESS);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		data->weapon = RIFLE;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		data->weapon = PISTOL;
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		data->weapon = KNIFE;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		handle_minimap(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		handle_door(data);
}
