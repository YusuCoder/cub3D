/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/18 16:54:49 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	radian(int degree)
{
	double	result;

	result = degree * (M_PI / 180);
	return (result);
}

// void	check_horizontal_intersection()
// {

// }

// void	ray_casting(t_data *data)
// {
// 	check_horizontal_intersection();
// 	check_verticalal_intersection();
// }

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

	// mlx_delete_image(data->mlx, data->img);
	int x = 0;
	while (x < data->width)
	{
		ray_angle = data->player.pov - (data->player.fov / 2) + (x / (double)data->width * data->player.fov);
		if (ray_angle < 0) ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI) ray_angle -= 2 * M_PI;
		// printf("ray_angle = %f\n", ray_angle);
		// printf("---------------------------------\n");

		ray_dir.x = cos(ray_angle);
		ray_dir.y = sin(ray_angle);
		// printf("ray_dir.x = %f\n", ray_dir.x);
		// printf("ray_dir.y = %f\n", ray_dir.y);
		// printf("---------------------------------\n");


		map.x = (int)data->player.pos.x;
		map.y = (int)data->player.pos.y;
		// printf("map.x = %d\n", map.x);
		// printf("map.y = %d\n", map.y);
		// printf("---------------------------------\n");


		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		// printf("delta_dist.x = %f\n", delta_dist.x);
		// printf("delta_dist.y = %f\n", delta_dist.y);
		// printf("---------------------------------\n");

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
		// printf("side_dist.x = %f\n", side_dist.x);
		// printf("side_dist.y = %f\n", side_dist.y);
		// printf("step.x = %d\n", step.x);
		// printf("step.y = %d\n", step.y);

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

		line_height = (int)data->height / plane_dist;
		draw_start = -line_height / 2 + data->height / 2;
		if (draw_start < 0) draw_start = 0;
		draw_end = line_height / 2 + data->height / 2;
		if (draw_end >= data->height) draw_end = data->height - 1;

		if (side == 1) wall_color = 0xFF8800FF;
		else wall_color = 0xFFFF00FF;

		// printf("x = %d\n", x);
		int y = draw_start;
		while (y < draw_end)
		{
			mlx_put_pixel(data->img, x, y, wall_color);
			// printf("y = %d\n", y);
			y++;
		}
		x++;
	}
}

void	render(void *param)
{
	t_data *data;

	data = param;
	ray_casting(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error_free_exit(data, NULL);
}

void	run_simulation(t_data *data)
{
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}
