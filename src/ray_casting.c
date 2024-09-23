/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:06:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/23 21:51:31 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	define_step_direction(t_ray *ray, t_player *player)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.column) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.column + 1.0 - player->pos.x) * ray->delta_dist.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.row) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.row + 1.0 - player->pos.y) * ray->delta_dist.y;
	}
}

void	define_ray_values(t_data *data, t_ray *ray, int x)
{
	t_player	*player;

	player = &data->player;
	// ray->angle = player->pov - (player->fov / 2) \
	// 	+ ((data->width - x) / (double)data->width * player->fov);
	ray->angle = player->pov - (player->fov / 2) \
		+ (x / (double)data->width * player->fov);
	// ray->angle = player->pov + (player->fov / 2) - (x / (double)data->width * player->fov);
	// int xx = (int)data->player.pos.x;
	// int yy = (int)data->player.pos.y;
	// printf("player angle = %f\n", player->pov * 180 / M_PI);
	// printf("player[x = %d][y = %d]\n", xx, yy);
	// while (data->map.map2d[xx][yy])
	// {
	// 	printf("[%d]%c\n", yy, (int)data->map.map2d[xx][yy]);
	// 	yy++;
	// }
	if (ray->angle < 0)
		ray->angle += radian(360);
	if (ray->angle > radian(360))
		ray->angle -= radian(360);
	ray->direction.x = cos(ray->angle);
	ray->direction.y = sin(ray->angle);
	ray->map.row = (int)player->pos.y;
	ray->map.column = (int)player->pos.x;
	ray->delta_dist.x = fabs(1 / ray->direction.x);
	ray->delta_dist.y = fabs(1 / ray->direction.y);
	define_step_direction(ray, player);
}

void	define_plane_distance(t_ray *ray, t_player *player)
{
	double	angle_difference;

	if (ray->side == 0)
	{
		ray->plane_dist = (ray->map.column - player->pos.x + (1 - ray->step.x) / 2) \
			/ ray->direction.x;
	}
	else
	{
		ray->plane_dist = (ray->map.row - player->pos.y + (1 - ray->step.y) / 2) \
			/ ray->direction.y;
	}
	angle_difference = ray->angle - player->pov;
	ray->plane_dist *= cos(angle_difference);
}

void	define_wall_collision(t_data *data, t_ray *ray)
{
	int	wall_hit;

	wall_hit = 0;
	while (wall_hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.column += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.row += ray->step.y;
			ray->side = 1;
		}
		if (data->map.map2d[ray->map.row][ray->map.column] == '1')
			wall_hit = 1;
	}
	define_plane_distance(ray, &data->player);
}

void	ray_casting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < data->width)
	{
		define_ray_values(data, &ray, x);
		define_wall_collision(data, &ray);
		rendering(data, &ray, x);
		x++;
	}
}
