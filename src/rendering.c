/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/19 17:49:49 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	radian(int degree)
{
	double	result;

	result = degree * (M_PI / 180);
	return (result);
}

void	ray_casting(t_data *data)
{
	double			ray_angle;
	t_point_double	ray_dir;
	t_point_int		map;
	t_point_double	delta_dist;
	t_point_int		step;
	t_point_double	side_dist;
	int				hit;
	int				side;
	double			plane_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				wall_color;

	int x = 0;
	while (x < data->width)
	{
		ray_angle = data->player.pov - (data->player.fov / 2) + ((data->width - x) / (double)data->width * data->player.fov);
		if (ray_angle < 0) ray_angle += radian(360);
		if (ray_angle > radian(360)) ray_angle -= radian(360);
		printf("player->pov = %f radians\n", data->player.pov);
		printf("player->pov = %f degrees\n", data->player.pov * 180 / M_PI);
		printf("ray_angle = %f radians\n", ray_angle);
		printf("ray_angle = %f degrees\n", ray_angle * 180 / M_PI);

		ray_dir.x = cos(ray_angle);
		ray_dir.y = sin(ray_angle);

		map.x = (int)data->player.pos.x;
		map.y = (int)data->player.pos.y;

		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);

		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (data->player.pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - data->player.pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (data->player.pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - data->player.pos.y) * delta_dist.y;
		}

		hit = 0;
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (data->map.map2d[map.x][map.y] == '1') hit = 1;
		}

		if (side == 0)
			plane_dist = (map.x - data->player.pos.x + (1 - step.x) / 2) / ray_dir.x;
		else
			plane_dist = (map.y - data->player.pos.y + (1 - step.y) / 2) / ray_dir.y;
		double	angle_difference = ray_angle - data->player.pov;
		plane_dist *= cos(angle_difference);

		line_height = (int)data->height / plane_dist;
		draw_start = -line_height / 2 + data->height / 2;
		if (draw_start < 0) draw_start = 0;
		draw_end = line_height / 2 + data->height / 2;
		if (draw_end >= data->height) draw_end = data->height - 1;

		if (side == 1) wall_color = 0xFF8800FF;
		else wall_color = 0xFFFF00FF;

		int y = draw_start;
		while (y < draw_end)
		{
			mlx_put_pixel(data->img, x, y, wall_color);
			y++;
		}
		x++;
	}
}

void	move_player(t_data *data, double move_x, double move_y)
{
	t_map		*map;
	t_player	*player;
	double		new_x;
	double		new_y;

	map = &data->map;
	player = &data->player;
	new_x = player->pos.x + move_x;
	new_y = player->pos.y + move_y;
	if (map->map2d[(int)new_x][(int)player->pos.y] != '1')
		player->pos.x = new_x;
	if (map->map2d[(int)player->pos.x][(int)new_y] != '1')
		player->pos.y = new_y;
}

void	action_handling(t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, cos(player->pov) * MOVE, sin(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -cos(player->pov) * MOVE, -sin(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, -sin(player->pov) * MOVE, cos(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, sin(player->pov) * MOVE, -cos(player->pov) * MOVE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.pov -= ROTATE;
		if (data->player.pov < 0)
			data->player.pov += radian(360);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.pov += ROTATE;
		if (data->player.pov > radian(360))
			data->player.pov -= radian(360);
	}
}

void	set_colors(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (y < data->height / 2)
				mlx_put_pixel(data->img, x, y, data->texture.ceiling);
			else
				mlx_put_pixel(data->img, x, y, data->texture.floor);
			x++;
		}
		y++;
	}
}

void	rendering(void *param)
{
	t_data *data;

	data = param;
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, "Failed to create mlx image");
	set_colors(data);
	action_handling(data);
	ray_casting(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error_free_exit(data, "Failed to display mlx image");
}
