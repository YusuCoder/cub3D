/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:40:38 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/01 19:17:39 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_tile_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE)
	{
		j = 0;
		while (j < MINIMAP_TILE)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int	set_color(char **map, uint32_t *color, t_point_int pos, char symbol)
{
	char	tile;

	tile = map[pos.y][pos.x];
	if (tile == ' ')
		return (0);
	else if (tile == '1')
		*color = MINIMAP_WALL;
	else if (tile == '0' || tile == symbol)
		*color = MINIMAP_EMPTY;
	return (1);
}

void	draw_minimap_tiles(t_map *map, t_point_int offset, mlx_image_t *img)
{
	t_point_int	pos;
	t_point_int	i;
	uint32_t	color;

	i.y = -1;
	while (++i.y < MINIMAP_H / MINIMAP_TILE)
	{
		pos.y = offset.y + i.y;
		if ((pos.y >= map->height) || (pos.y < 0))
			continue ;
		i.x = -1;
		while (++i.x < MINIMAP_W / MINIMAP_TILE)
		{
			pos.x = offset.x + i.x;
			if (pos.x < 0
				|| pos.x >= (int)ft_strlen(map->map2d[pos.y])
				|| !set_color(map->map2d, &color, pos, map->player_direction))
				continue ;
			set_tile_pixel(img, i.x * MINIMAP_TILE, i.y * MINIMAP_TILE, color);
		}
	}
}

void	draw_minimap(t_data *data)
{
	t_point_int		offset;
	t_point_double	player;

	offset.x = (int)(data->player.pos.x - (MINIMAP_W / MINIMAP_TILE) / 2);
	offset.y = (int)(data->player.pos.y - (MINIMAP_H / MINIMAP_TILE) / 2);
	if (offset.x < 0)
		offset.x = 0;
	if (offset.y < 0)
		offset.y = 0;
	if (offset.x > data->map.width - MINIMAP_W / MINIMAP_TILE)
		offset.x = data->map.width - MINIMAP_W / MINIMAP_TILE;
	if (offset.y > data->map.height - MINIMAP_H / MINIMAP_TILE)
		offset.y = data->map.height - MINIMAP_H / MINIMAP_TILE;
	draw_minimap_tiles(&data->map, offset, data->img);
	player.x = (data->player.pos.x - offset.x) * MINIMAP_TILE;
	player.y = (data->player.pos.y - offset.y) * MINIMAP_TILE;
	set_tile_pixel(data->img, (int)player.x, (int)player.y, MINIMAP_PLAYER);
}
