/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:48:25 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/01 19:17:39 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_sprite(mlx_image_t *img, mlx_image_t *spr, int start_x, \
					int start_y)
{
	t_point_uint	pos_img;
	t_point_uint	pos_spr;
	int				index_img;
	int				index_spr;
	uint8_t			alpha;

	pos_img.y = start_y;
	pos_spr.y = 0;
	while (pos_img.y < start_y + spr->height)
	{
		pos_img.x = start_x;
		pos_spr.x = 0;
		while (pos_img.x < start_x + spr->width)
		{
			index_img = (pos_img.y * img->width + pos_img.x) * 4;
			index_spr = (pos_spr.y * spr->width + pos_spr.x) * 4;
			alpha = spr->pixels[index_spr + 3];
			if (alpha != 0)
				memcpy(&img->pixels[index_img], &spr->pixels[index_spr], 4);
			pos_img.x++;
			pos_spr.x++;
		}
		pos_img.y++;
		pos_spr.y++;
	}
}
