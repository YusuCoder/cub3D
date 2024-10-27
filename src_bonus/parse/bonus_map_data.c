/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:29:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/27 16:26:15 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	*check_color(int *color, char **rgb_code)
{
	color = malloc(sizeof(int) * 3);
	if (!color)
	{
		free_map(rgb_code);
		return (0);
	}
	if (!cp_color(rgb_code, color))
	{
		free_map(rgb_code);
		return (0);
	}
	free_map(rgb_code);
	return (color);
}

static int	*set_color_code(char *map, t_data *data)
{
	int		*color;
	int		i;
	char	**rgb_code;

	(void)data;
	color = NULL;
	rgb_code = ft_split(map, ',');
	if (!rgb_code)
		return (0);
	i = 0;
	while (rgb_code[i])
		i++;
	if (i != 3)
	{
		free_map(rgb_code);
		return (0);
	}
	color = check_color(color, rgb_code);
	if (color == 0)
		return (0);
	return (color);
}

int	rgb_codes(t_data *data, char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (rgb[i][0] == 'C')
		{
			data->texture.rgb_cell = set_color_code(rgb[i] + 1, data);
			if (data->texture.rgb_cell == 0)
				return (error_msg("rgb color error.", 1));
		}
		else if (rgb[i][0] == 'F')
		{
			data->texture.rgb_floor = set_color_code(rgb[i] + 1, data);
			if (data->texture.rgb_floor == 0)
				return (error_msg("rgb color error.", 1));
		}
		else
			return (error_msg("Error!", 1));
		i++;
	}
	return (0);
}

void	map_data(t_data *data)
{
	if (set_path(&data->map, data->texture.tex_path) == 1)
	{
		free_map(data->texture.tex_path);
		free_map(data->texture.rgb_codes);
		free_map(data->map.map2d);
		free_path(data);
		exit(EXIT_FAILURE);
	}
	if (rgb_codes(data, data->texture.rgb_codes) == 1)
	{
		free_path(data);
		if (data->texture.rgb_floor)
			free(data->texture.rgb_floor);
		free_map(data->texture.rgb_codes);
		free_map(data->map.map2d);
		exit(EXIT_FAILURE);
	}
	free_map(data->texture.rgb_codes);
}
