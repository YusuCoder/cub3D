/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:25:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/17 12:44:34 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_player *player, t_map *map)
{
	player->fov = radian(VIEW);
	player->pos.x = (map->player_position.x * GRIDSIZE) + (GRIDSIZE / 2);
	player->pos.y = (map->player_position.y * GRIDSIZE) + (GRIDSIZE / 2);
	if (map->player_direction == 'N')
		player->pov = 90;
	else if (map->player_direction == 'S')
		player->pov = 270;
	else if (map->player_direction == 'E')
		player->pov = 0;
	else if (map->player_direction == 'W')
		player->pov = 180;
}

void	init_map(t_map *map)
{
	map->map2d = (char **)malloc(7 * sizeof(char));
	if (map->map2d == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	map->map2d[0] = ft_strdup(" 111111 ");
	map->map2d[1] = ft_strdup("10001001");
	map->map2d[2] = ft_strdup("10001001");
	map->map2d[3] = ft_strdup("10001001");
	map->map2d[4] = ft_strdup("10000001");
	map->map2d[5] = ft_strdup("10000N01");
	map->map2d[6] = ft_strdup(" 111111 ");
	map->player_direction = 'N';
	map->player_position.x = 5;
	map->player_position.y = 5;
}

void	init_data(t_data *data)
{
	init_map(&data->map);
	init_player(&data->player, &data->map);
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	if (data->mlx == NULL)
		error_exit(data);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_exit(data);
}
