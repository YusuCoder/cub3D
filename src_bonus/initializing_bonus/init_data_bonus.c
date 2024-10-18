/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:25:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/18 18:09:25 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	init_data(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->buf = NULL;
	data->is_minimap = true;
	data->is_door = false;
	data->door.status = CLOSED;
	data->weapon = RIFLE;
	data->is_playing_sound = false;
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	if (data->mlx == NULL)
		error_free_exit(data, "Failed to create mlx");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	init_map(data);
	init_player(data);
	init_texture(data);
	init_sprites(data);
}
