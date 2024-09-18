/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:25:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/18 16:54:47 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_data *data)
{
	t_player	*player;
	t_map		*map;

	player = &data->player;
	map = &data->map;
	player->fov = radian(VIEW);
	player->pos.x = map->player_position.x + 0.5;
	player->pos.y = map->player_position.y + 0.5;
	if (map->player_direction == 'N')
		player->pov = radian(90);
	else if (map->player_direction == 'S')
		player->pov = radian(270);
	else if (map->player_direction == 'E')
		player->pov = radian(0);
	else if (map->player_direction == 'W')
		player->pov = radian(180);
}

void	init_map(t_data *data)
{
	t_map	*map;

	map = &data->map;
	map->map2d = (char **)malloc(8 * sizeof(char *));
	if (map->map2d == NULL)
		error_free_exit(data, "malloc");
	map->map2d[0] = ft_strdup(" 111111 ");
	map->map2d[1] = ft_strdup("10001001");
	map->map2d[2] = ft_strdup("10001001");
	map->map2d[3] = ft_strdup("10001001");
	map->map2d[4] = ft_strdup("10000001");
	map->map2d[5] = ft_strdup("10000N01");
	map->map2d[6] = ft_strdup(" 111111 ");
	map->map2d[7] = NULL;
	map->player_direction = 'N';
	map->player_position.x = 5;
	map->player_position.y = 5;
}

void	init_data(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	init_map(data);
	init_player(data);
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	if (data->mlx == NULL)
		error_free_exit(data, NULL);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_free_exit(data, NULL);
}
