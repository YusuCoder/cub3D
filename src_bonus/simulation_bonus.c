/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/27 16:31:20 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	handle_timer(t_data *data)
{
	if (data->timer_active)
	{
		data->timer_active = 0;
		printf("----------------->Timer turned off.<---------------\n");
	}
	else
	{
		data->timer_active = 1;
		data->timer_start = time(NULL);
		printf("----------------->Timer turned on.<----------------\n");
	}
}

/*-----------------------------------------------------*/
/*  Set counter to skip first 2 frames of game screen  */
/*-----------------------------------------------------*/
void	set_counter(t_data *data, int *counter)
{
	if (counter == NULL)
		*counter = 0;
	else
		(*counter)++;
	if (*counter < 3)
		mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}

void	time_checker(t_data *data)
{
	time_t	current_time;
	double	elapsed_time;

	if (data->timer_active)
	{
		current_time = time(NULL);
		elapsed_time = difftime(current_time, data->timer_start);
		if (elapsed_time >= 10 && !data->game_over)
		{
			game_over();
			data->game_over = 1;
		}
		if (elapsed_time >= 20)
		{
			printf("-------------->Time's up! Exiting game...\n");
			free_exit(data, EXIT_SUCCESS);
		}
	}
}

void	another_simulation(t_data *data, t_sprite *sprite)
{
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	movement_handler(data);
	ray_casting(data);
	if (data->is_minimap)
		draw_minimap(data);
	draw_aim(data->img, sprite->aim);
	draw_weapon(data, sprite);
}

/*-------------------------*/
/*  Start game simulation  */
/*-------------------------*/
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
	time_checker(data);
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	another_simulation(data, sprite);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error_free_exit(data, "Failed to display mlx image");
}
