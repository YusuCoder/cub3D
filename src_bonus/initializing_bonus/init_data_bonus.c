/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:25:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:33 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*--------------------------*/
/*  Initialize data struct  */
/*--------------------------*/

void	init_null(mlx_image_t *image[], int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		image[i] = NULL;
		i++;
	}
}

void	init_vars(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->buf = NULL;
	data->img = NULL;
	data->texture.east = NULL;
	data->texture.west = NULL;
	data->texture.north = NULL;
	data->texture.south = NULL;
	data->texture.door = NULL;
	data->sprite.aim = NULL;
}

void	init_data(t_data *data)
{
	init_vars(data);
	init_null(data->sprite.rifle, 6);
	init_null(data->sprite.bullet, 6);
	init_null(data->sprite.pistol, 9);
	init_null(data->sprite.knife, 7);
	data->is_minimap = true;
	data->is_door = false;
	data->weapon = RIFLE;
	data->is_playing_sound = false;
	data->mlx = NULL;
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
