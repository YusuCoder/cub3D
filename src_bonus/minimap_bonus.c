/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:40:38 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/20 14:21:32 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_tile_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < M_TILE)
	{
		j = 0;
		while (j < M_TILE)
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
		*color = M_WALL;
	else if (tile == '0' || tile == symbol)
		*color = M_EMPTY;
	return (1);
}

void	draw_minimap_tiles(t_map *map, t_point_int offset, mlx_image_t *img)
{
	t_point_int	pos;
	t_point_int	i;
	uint32_t	color;

	i.y = -1;
	color = 0;
	while (++i.y < M_HEIGHT / M_TILE)
	{
		pos.y = offset.y + i.y;
		if ((pos.y >= map->height) || (pos.y < 0))
			continue ;
		i.x = -1;
		while (++i.x < M_WIDTH / M_TILE)
		{
			pos.x = offset.x + i.x;
			if (pos.x < 0
				|| pos.x >= (int)ft_strlen(map->map2d[pos.y])
				|| !set_color(map->map2d, &color, pos, map->player_direction))
				continue ;
			set_tile_pixel(img, i.x * M_TILE, i.y * M_TILE, color);
		}
	}
}

void	draw_minimap_player(char **map, t_point_double pos_map, \
							t_point_int offset, mlx_image_t *img)
{
	t_point_double	pos;
	double			limit;
	char			tile_x;
	char			tile_y;

	limit = M_TILE / 2;
	pos.x = (pos_map.x - offset.x) * M_TILE;
	pos.y = (pos_map.y - offset.y) * M_TILE;
	tile_x = map[(int)pos_map.y][(int)(pos_map.x + limit / M_TILE)];
	tile_y = map[(int)(pos_map.y + limit / M_TILE)][(int)pos_map.x];
	if ((tile_x == '1' || tile_x == '2')
		&& fmod(pos.x, M_TILE) > M_TILE - limit)
		pos.x = (floor(pos.x / M_TILE) + 1) * M_TILE - limit;
	else if ((tile_x == '1' || tile_x == '2')
		&& fmod(pos.x, M_TILE) < limit)
		pos.x = floor(pos.x / M_TILE) * M_TILE + limit;
	if ((tile_y == '1' || tile_y == '2')
		&& fmod(pos.y, M_TILE) > M_TILE - limit)
		pos.y = (floor(pos.y / M_TILE) + 1) * M_TILE - limit;
	else if ((tile_y == '1' || tile_y == '2')
		&& fmod(pos.y, M_TILE) < limit)
		pos.y = floor(pos.y / M_TILE) * M_TILE + limit;
	set_tile_pixel(img, (int)pos.x - limit, (int)pos.y - limit, M_PLAYER);
}

void	draw_minimap(t_data *data)
{
	t_point_int	offset;

	offset.x = (int)(data->player.pos.x - (M_WIDTH / M_TILE) / 2);
	offset.y = (int)(data->player.pos.y - (M_HEIGHT / M_TILE) / 2);
	if (offset.x < 0)
		offset.x = 0;
	if (offset.y < 0)
		offset.y = 0;
	if (offset.x > data->map.width - M_WIDTH/ M_TILE)
		offset.x = data->map.width - M_WIDTH / M_TILE;
	if (offset.y > data->map.height - M_HEIGHT / M_TILE)
		offset.y = data->map.height - M_HEIGHT / M_TILE;
	draw_minimap_tiles(&data->map, offset, data->img);
	draw_minimap_player(data->map.map2d, data->player.pos, offset, data->img);
}
