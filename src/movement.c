/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:39:43 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/26 14:51:00 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*------------------------------------------------------*/
/*  Getting a symbol of position moving on x direction  */
/*------------------------------------------------------*/
int	get_tile_x(t_map *map, t_point_double new, t_player *player, double move_x)
{
	int	tile_index_x;
	int	player_tile_y;

	player_tile_y = (int)(player->pos.y);
	if (move_x > 0)
		tile_index_x = (int)(new.x + PADDING);
	else
		tile_index_x = (int)(new.x - PADDING);
	return (map->map2d[player_tile_y][tile_index_x]);
}

/*------------------------------------------------------*/
/*  Getting a symbol of position moving on y direction  */
/*------------------------------------------------------*/
int	get_tile_y(t_map *map, t_point_double new, t_player *player, double move_y)
{
	int	tile_index_y;
	int	player_tile_x;

	player_tile_x = (int)(player->pos.x);
	if (move_y > 0)
		tile_index_y = (int)(new.y + PADDING);
	else
		tile_index_y = (int)(new.y - PADDING);
	return (map->map2d[tile_index_y][player_tile_x]);
}

/*-------------------------------------------------------------*/
/*  Getting a symbol of position moving on diagonal direction  */
/*-------------------------------------------------------------*/
int	get_tile_diag(t_map *map, t_point_double new, double move_x, double move_y)
{
	int	tile_index_y;
	int	tile_index_x;

	if (move_y > 0)
		tile_index_y = (int)(new.y + PADDING);
	else
		tile_index_y = (int)(new.y - PADDING);
	if (move_x > 0)
		tile_index_x = (int)(new.x + PADDING);
	else
		tile_index_x = (int)(new.x - PADDING);
	if (move_x != 0 && move_y != 0)
		return (map->map2d[tile_index_y][tile_index_x]);
	return ('0');
}
