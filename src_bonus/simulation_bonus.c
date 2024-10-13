/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/12 21:15:20 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_counter(t_data *data, int *counter)
{
	if (counter == NULL)
		*counter = 0;
	else
		(*counter)++;
	if (*counter < 3)
		mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}

void	simulation(void *param)
{
	t_data		*data;
	t_sprite	*sprite;
	static int	counter;

	data = param;
	sprite = &data->sprite;
	if (counter < 3)
	{
		set_counter(data, &counter);
		return ;
	}
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	movement_handler(data);
	ray_casting(data);
	if (data->is_minimap)
		draw_minimap(data);
	draw_aim(data->img, sprite->aim);
	draw_weapon(data, sprite, data->img);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error_free_exit(data, "Failed to display mlx image");
}
