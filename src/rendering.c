/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:41:30 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/23 15:44:48 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_wall_textures(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	wall_color;

	if (ray->side == 1)
		wall_color = 0xFF8800FF;
	else
		wall_color = 0xFFFF00FF;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		mlx_put_pixel(data->img, x, y, wall_color);
		y++;
	}
}

void	set_ceiling_floor_colors(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(data->img, x, y, data->texture.ceiling);
		y++;
	}
	y = ray->draw_end;
	while (y < data->height)
	{
		mlx_put_pixel(data->img, x, y, data->texture.floor);
		y++;
	}
}

void	rendering(t_data *data, t_ray *ray, int x)
{
	ray->line_height = (int)data->height / ray->plane_dist;
	ray->draw_start = -(ray->line_height) / 2 + data->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->height / 2;
	if (ray->draw_end >= data->height)
		ray->draw_end = data->height - 1;
	set_ceiling_floor_colors(data, ray, x);
	set_wall_textures(data, ray, x);
}