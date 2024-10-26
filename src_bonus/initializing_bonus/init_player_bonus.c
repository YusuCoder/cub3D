/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:06:51 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/20 16:14:34 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*------------------------*/
/*  Invert player's view  */
/*------------------------*/
void	invert_view(t_player *player)
{
	if (player->pov == NORTH)
		player->angle = radian(270);
	else if (player->pov == SOUTH)
		player->angle = radian(90);
	else if (player->pov == EAST)
		player->angle = radian(0);
	else if (player->pov == WEST)
		player->angle = radian(180);
}

/*----------------------------*/
/*  Initialize player struct  */
/*----------------------------*/
void	init_player(t_data *data)
{
	t_player	*player;
	t_map		*map;

	player = &data->player;
	map = &data->map;
	player->angle = 0;
	player->fov = radian(VIEW);
	player->pos.x = map->player_position.x + 0.5;
	player->pos.y = map->player_position.y + 0.5;
	if (map->player_direction == 'N')
		player->pov = NORTH;
	else if (map->player_direction == 'S')
		player->pov = SOUTH;
	else if (map->player_direction == 'E')
		player->pov = EAST;
	else if (map->player_direction == 'W')
		player->pov = WEST;
	invert_view(player);
}
