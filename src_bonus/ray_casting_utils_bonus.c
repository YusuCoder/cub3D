/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:31:34 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/20 16:29:58 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*--------------------------------------*/
/*  Define distance to the image plane  */
/*--------------------------------------*/
void	define_plane_distance(t_ray *ray, t_player *player)
{
	double	angle_difference;

	if (ray->side == VERTICAL)
	{
		ray->plane_dist = (ray->map.column - player->pos.x + \
							(1 - ray->step.x) / 2) / ray->direction.x;
	}
	else
	{
		ray->plane_dist = (ray->map.row - player->pos.y + \
							(1 - ray->step.y) / 2) / ray->direction.y;
	}
	angle_difference = ray->angle - player->angle;
	angle_difference = fmod(angle_difference + M_PI, 2 * M_PI) - M_PI;
	ray->plane_dist *= cos(angle_difference);
	ray->direction.x /= cos(angle_difference);
	ray->direction.y /= cos(angle_difference);
}

/*--------------------------------------*/
/*  Define the side where wall appears  */
/*--------------------------------------*/
void	define_wall_side(t_ray *ray)
{
	if (ray->side == VERTICAL)
	{
		if (ray->step.x > 0)
			ray->wall = EAST;
		else
			ray->wall = WEST;
	}
	else if (ray->side == HORIZONTAL)
	{
		if (ray->step.y > 0)
			ray->wall = SOUTH;
		else
			ray->wall = NORTH;
	}
}

/*-------------------------------*/
/*  Define door collision point  */
/*-------------------------------*/
void	define_door_collision(t_data *data, t_ray *ray, int *wall_hit)
{
	if (data->map.map2d[ray->map.row][ray->map.column] == '2'
		|| data->map.map2d[ray->map.row][ray->map.column] == 'O')
	{
		if (data->map.map2d[ray->map.row][ray->map.column] == '2')
			*wall_hit = 1;
		data->is_door = true;
		data->door.is_close = false;
		data->door.dist = sqrt(pow(ray->map.column - data->player.pos.x, 2) + \
							pow(ray->map.row - data->player.pos.y, 2));
		if (data->door.dist <= 2.2)
		{
			data->door.is_close = true;
			data->door.pos.x = ray->map.column;
			data->door.pos.y = ray->map.row;
		}
	}
	else
		data->is_door = false;
}

/*-------------------------------*/
/*  Define wall collision point  */
/*-------------------------------*/
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
			ray->side = VERTICAL;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.row += ray->step.y;
			ray->side = HORIZONTAL;
		}
		if (data->map.map2d[ray->map.row][ray->map.column] == '1')
			wall_hit = 1;
		else
			define_door_collision(data, ray, &wall_hit);
	}
	define_plane_distance(ray, &data->player);
	define_wall_side(ray);
}

/*------------------------*/
/*  Define ray direction  */
/*------------------------*/
void	define_step_direction(t_ray *ray, t_player *player)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.column) \
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.column + 1.0 - player->pos.x) \
							* ray->delta_dist.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.row) \
							* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.row + 1.0 - player->pos.y) \
							* ray->delta_dist.y;
	}
}
