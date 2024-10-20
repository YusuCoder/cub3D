/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:06:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/20 16:21:23 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*----------------------------*/
/*  Ray casting calculations  */
/*----------------------------*/
void	ray_casting(t_data *data)
{
	t_ray	*ray;
	int		x;

	ray = &data->ray;
	x = 0;
	while (x < data->width)
	{
		ray->angle = data->player.angle + atan((2.0 * x / data->width - 1.0) \
					* tan(data->player.fov / 2));
		ray->angle = fmod(ray->angle, radian(360));
		if (ray->angle < 0)
			ray->angle += radian(360);
		ray->direction.x = cos(ray->angle);
		ray->direction.y = sin(ray->angle);
		ray->map.row = (int)data->player.pos.y;
		ray->map.column = (int)data->player.pos.x;
		ray->delta_dist.x = fabs(1 / ray->direction.x);
		ray->delta_dist.y = fabs(1 / ray->direction.y);
		define_step_direction(ray, &data->player);
		define_wall_collision(data, ray);
		rendering(data, ray, x);
		x++;
	}
}
