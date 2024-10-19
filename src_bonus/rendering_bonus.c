/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:41:30 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/18 20:52:09 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	index;
	int	pixel;

	index = (y * texture->width + x) * 4;
	pixel = (texture->pixels[index + 0] << 24) \
			| (texture->pixels[index + 1] << 16) \
			| (texture->pixels[index + 2] << 8) \
			| (texture->pixels[index + 3]);
	return (pixel);
}

void	define_texture_values(t_data *data, t_ray *ray, \
							mlx_texture_t **texture, double *wall_x)
{
	if (data->is_door
		&& data->map.map2d[ray->map.row][ray->map.column] == '2')
		*texture = data->texture.test;
	else
	{
		if (ray->wall == NORTH)
			*texture = data->texture.north;
		else if (ray->wall == SOUTH)
			*texture = data->texture.south;
		else if (ray->wall == EAST)
			*texture = data->texture.east;
		else if (ray->wall == WEST)
			*texture = data->texture.west;
	}
	if (ray->side == VERTICAL)
		*wall_x = data->player.pos.y + ray->plane_dist * ray->direction.y;
	else
		*wall_x = data->player.pos.x + ray->plane_dist * ray->direction.x;
	*wall_x -= floor(*wall_x);
}

void	draw_walls(t_data *data, t_ray *ray, int x, int y)
{
	t_point_int		tex;
	double			wall_x;
	double			step;
	double			tex_pos;
	mlx_texture_t	*texture;

	wall_x = 0.0;
	define_texture_values(data, ray, &texture, &wall_x);
	tex.x = (int)(wall_x * texture->width);
	if ((ray->side == VERTICAL && ray->direction.x < 0)
		|| (ray->side == HORIZONTAL && ray->direction.y > 0))
		tex.x = texture->width - tex.x - 1;
	step = (double)texture->height / ray->line_height;
	tex_pos = (ray->draw_start - data->height / 2 + ray->line_height / 2) \
				* step;
	while (y < ray->draw_end)
	{
		tex.y = (int)tex_pos;
		if (tex.y >= (int)texture->height)
			tex.y = (int)texture->height - 1;
		tex_pos += step;
		mlx_put_pixel(data->img, x, y, get_pixel(texture, tex.x, tex.y));
		y++;
	}
}

void	draw_ceiling_floor(t_data *data, t_ray *ray, int x)
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
	draw_ceiling_floor(data, ray, x);
	draw_walls(data, ray, x, ray->draw_start);
}
