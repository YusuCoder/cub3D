/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:36:56 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/18 12:13:35 by ryusupov         ###   ########.fr       */
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

/*----------------------------------------*/
/*  Handle pushing buttons on a keyboard  */
/*----------------------------------------*/
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		free_exit(data, EXIT_SUCCESS);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		if (data->is_minimap == true)
			data->is_minimap = false;
		else
			data->is_minimap = true;
	}
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		data->weapon = RIFLE;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		data->weapon = PISTOL;
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		data->weapon = KNIFE;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (data->door.is_close == true && data->door.status == CLOSED)
			data->door.status = OPEN;
		else if (data->door.is_close == true && data->door.status == OPEN)
			data->door.status = CLOSED;
	}
	// printf("is_door = %d\n", data->is_door);
	// printf("is_close = %d\n", data->door.is_close);
	// printf("door_pos.x = %d\n", data->door.pos.x);
	// printf("door_pos.y = %d\n", data->door.pos.y);
	// printf("door dist = %f\n", data->door.dist);
}
