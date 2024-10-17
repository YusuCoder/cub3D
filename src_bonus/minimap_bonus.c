/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:40:38 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/17 15:24:58 by tkubanyc         ###   ########.fr       */
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

void	draw_minimap_player(char **map, t_point_double pos_map, \
							t_point_int offset, mlx_image_t *img)
{
	t_point_double	pos_minimap;
	double			limit;
	// char			tile_x;
	// char			tile_y;

	limit = MINIMAP_TILE / 2;
	pos_minimap.x = (pos_map.x - offset.x) * MINIMAP_TILE;
	pos_minimap.y = (pos_map.y - offset.y) * MINIMAP_TILE;
	if (map[(int)pos_map.y][(int)(pos_map.x + limit / MINIMAP_TILE)] == '1'
		&& fmod(pos_minimap.x, MINIMAP_TILE) > MINIMAP_TILE - limit)
		pos_minimap.x = (floor(pos_minimap.x / MINIMAP_TILE) + 1) \
						* MINIMAP_TILE - limit;
	else if (map[(int)pos_map.y][(int)(pos_map.x - limit / MINIMAP_TILE)] == '1'
		&& fmod(pos_minimap.x, MINIMAP_TILE) < limit)
		pos_minimap.x = floor(pos_minimap.x / MINIMAP_TILE) \
						* MINIMAP_TILE + limit;
	if (map[(int)(pos_map.y + limit / MINIMAP_TILE)][(int)pos_map.x] == '1'
		&& fmod(pos_minimap.y, MINIMAP_TILE) > MINIMAP_TILE - limit)
		pos_minimap.y = (floor(pos_minimap.y / MINIMAP_TILE) + 1) \
						* MINIMAP_TILE - limit;
	else if (map[(int)(pos_map.y - limit / MINIMAP_TILE)][(int)pos_map.x] == '1'
			&& fmod(pos_minimap.y, MINIMAP_TILE) < limit)
		pos_minimap.y = floor(pos_minimap.y / MINIMAP_TILE) \
						* MINIMAP_TILE + limit;
	set_tile_pixel(img, (int)pos_minimap.x - MINIMAP_TILE / 2, \
					(int)pos_minimap.y - MINIMAP_TILE / 2, MINIMAP_PLAYER);
}


void	draw_minimap(t_data *data)
{
	t_point_int	offset;

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
	draw_minimap_player(data->map.map2d, data->player.pos, offset, data->img);
}

// void	draw_minimap(t_data *data)
// {
// 	t_point_int	offset;
// 	int			map_width_in_tiles;
// 	int			map_height_in_tiles;

// 	map_width_in_tiles = data->map.width * MINIMAP_TILE;
// 	map_height_in_tiles = data->map.height * MINIMAP_TILE;

// 	// Center player unless near the edges of the map
// 	offset.x = (int)(data->player.pos.x * MINIMAP_TILE - MINIMAP_W / 2);
// 	offset.y = (int)(data->player.pos.y * MINIMAP_TILE - MINIMAP_H / 2);

// 	// Adjust to keep the minimap starting from the top-left corner if map is smaller
// 	if (map_width_in_tiles <= MINIMAP_W)
// 		offset.x = 0;
// 	else if (offset.x < 0)
// 		offset.x = 0;
// 	else if (offset.x > map_width_in_tiles - MINIMAP_W)
// 		offset.x = map_width_in_tiles - MINIMAP_W;

// 	if (map_height_in_tiles <= MINIMAP_H)
// 		offset.y = 0;
// 	else if (offset.y < 0)
// 		offset.y = 0;
// 	else if (offset.y > map_height_in_tiles - MINIMAP_H)
// 		offset.y = map_height_in_tiles - MINIMAP_H;

// 	// Draw the minimap tiles and player
// 	draw_minimap_tiles(&data->map, offset, data->img);
// 	draw_minimap_player(data->map.map2d, data->player.pos, offset, data->img);
// }

