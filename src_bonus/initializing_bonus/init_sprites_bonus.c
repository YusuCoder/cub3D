/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:08:13 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/13 19:16:57 by tkubanyc         ###   ########.fr       */
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
	if (!image)
		error_free_exit(data, "Failed to create mlx image");
	mlx_delete_texture(texture);
	return (image);
}

void	init_sprite_rifle(t_data *data, t_sprite *sprite)
{
	sprite->rifle[0] = new_sprite(data, "textures/sprite/rifle/rifle.png");
	sprite->rifle[1] = new_sprite(data, "textures/sprite/rifle/rifle_f1.png");
	sprite->rifle[2] = new_sprite(data, "textures/sprite/rifle/rifle_f2.png");
	sprite->rifle[3] = new_sprite(data, "textures/sprite/rifle/rifle_f3.png");
	sprite->rifle[4] = new_sprite(data, "textures/sprite/rifle/rifle_f4.png");
	sprite->rifle[5] = new_sprite(data, "textures/sprite/rifle/rifle_f5.png");
	sprite->bullet[0] = new_sprite(data, "textures/sprite/rifle/bullet1.png");
	sprite->bullet[1] = new_sprite(data, "textures/sprite/rifle/bullet2.png");
	sprite->bullet[2] = new_sprite(data, "textures/sprite/rifle/bullet3.png");
	sprite->bullet[3] = new_sprite(data, "textures/sprite/rifle/bullet4.png");
	sprite->bullet[4] = new_sprite(data, "textures/sprite/rifle/bullet5.png");
	sprite->bullet[5] = new_sprite(data, "textures/sprite/rifle/bullet6.png");
}

void	init_sprite_pistol(t_data *data, t_sprite *sprite)
{
	sprite->pistol[0] = new_sprite(data, "textures/sprite/pistol/pistol.png");
	sprite->pistol[1] = new_sprite(data, "textures/sprite/pistol/pistolF1.png");
	sprite->pistol[2] = new_sprite(data, "textures/sprite/pistol/pistolF2.png");
	sprite->pistol[3] = new_sprite(data, "textures/sprite/pistol/pistolF3.png");
	sprite->pistol[4] = new_sprite(data, "textures/sprite/pistol/pistolF4.png");
	sprite->pistol[5] = new_sprite(data, "textures/sprite/pistol/pistolF5.png");
	sprite->pistol[6] = new_sprite(data, "textures/sprite/pistol/pistolF6.png");
	sprite->pistol[7] = new_sprite(data, "textures/sprite/pistol/pistolF7.png");
	sprite->pistol[8] = new_sprite(data, "textures/sprite/pistol/pistolF8.png");
}

void	init_sprite_knife(t_data *data, t_sprite *sprite)
{
	sprite->knife[0] = new_sprite(data, "textures/sprite/knife/Knife.png");
	sprite->knife[1] = new_sprite(data, "textures/sprite/knife/KnifeF01.png");
	sprite->knife[2] = new_sprite(data, "textures/sprite/knife/KnifeF02.png");
	sprite->knife[3] = new_sprite(data, "textures/sprite/knife/KnifeF03.png");
	sprite->knife[4] = new_sprite(data, "textures/sprite/knife/KnifeF04.png");
	sprite->knife[5] = new_sprite(data, "textures/sprite/knife/KnifeF05.png");
	sprite->knife[6] = new_sprite(data, "textures/sprite/knife/KnifeF06.png");
}

void	init_sprites(t_data *data)
{
	t_sprite	*sprite;

	sprite = &data->sprite;
	sprite->aim = new_sprite(data, "textures/sprite/aim.png");
	init_sprite_rifle(data, sprite);
	init_sprite_pistol(data, sprite);
	init_sprite_knife(data, sprite);
}
