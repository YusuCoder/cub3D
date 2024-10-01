/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:08:13 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/01 19:31:54 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static mlx_image_t	*new_sprite(t_data *data, char *sprite_path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(sprite_path);
	if (!texture)
		error_free_exit(data, "Failed to create mlx texture");
	image = mlx_texture_to_image(data->mlx, texture);
	if (!data->sprite.aim)
		error_free_exit(data, "Failed to create mlx image");
	mlx_delete_texture(texture);
	return (image);
}

void	init_sprites(t_data *data)
{
	t_sprite	*sprite;

	sprite = &data->sprite;
	sprite->aim = new_sprite(data, "textures/sprite/aim.png");
	sprite->rifle = new_sprite(data, "textures/sprite/rifle.png");
}
