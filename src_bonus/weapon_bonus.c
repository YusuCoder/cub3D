/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:44:18 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/13 20:18:51 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_bullet(mlx_image_t *img, t_sprite *sprite, int frame)
{
	mlx_image_t	*curr_sprite;
	t_point_int	start;
	int			limit;

	limit = 7;
	if (frame >= limit)
		return ;
	curr_sprite = sprite->bullet[frame];
	start.x = img->width / 2 + (img->width / 2 - curr_sprite->width);
	start.y = img->height / 2 + (img->height / 2 - curr_sprite->height);
	draw_sprite(img, curr_sprite, start.x, start.y);
}

t_point_int	set_start_point(t_weapon weapon, mlx_image_t *img, \
							mlx_image_t *curr)
{
	t_point_int	start;

	if (weapon == KNIFE)
	{
		start.x = img->width / 2 - curr->width / 2;
		start.y = img->height / 2 + (img->height / 2 - curr->height);
	}
	else
	{
		start.x = img->width / 2 + (img->width / 2 - curr->width);
		start.y = img->height / 2 + (img->height / 2 - curr->height);
	}
	return (start);
}

void	draw_weapon_frame(t_data *data, mlx_image_t *curr, int frame)
{
	t_point_int	start;

	if (data->weapon == RIFLE)
		draw_bullet(data->img, &data->sprite, frame - 1);
	start = set_start_point(data->weapon, data->img, curr);
	draw_sprite(data->img, curr, start.x, start.y);
}

void	draw_weapon(t_data *data, t_sprite *sprite)
{
	static int	frame;
	static bool	shoot;
	int			limit;
	mlx_image_t	*curr;

	limit = set_frame_limit(data->weapon);
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		shoot = true;
		frame = 0;
	}
	if (!shoot)
		frame = 0;
	if (shoot)
	{
		frame++;
		if (frame >= limit)
		{
			shoot = false;
			frame = 0;
		}
	}
	curr = set_current_frame(data->weapon, sprite, frame);
	draw_weapon_frame(data, curr, frame);
}
