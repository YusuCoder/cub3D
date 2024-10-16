/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:29:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/16 17:08:49 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

char	*get_path(char *map, int j)
{
	int		i;
	int		length;
	char	*path;

	length = 1;
	i = 0;
	while (map[j] && (map[j] == ' ' || map[j] == '\t'))
		j++;
	while (map[length] && (map[length] != ' ' || map[length] != '\t'))
		length++;
	path = malloc(sizeof(char) * (length - j + 1));
	if (path == NULL)
		return (NULL);
	while (map[j] && (map[j] != ' ' && map[j] != '\t' && map[j] != '\n'))
		path[i++] = map[j++];
	path[i] = '\0';
	while (map[j] && (map[j] == ' ' || map[j] == '\t'))
		j++;
	if (map[j] && (map[j] != '\n'))
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	is_not_digit(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			check = 0;
		i++;
	}
	return (check);
}

int	*cp_color(char **rgb, int *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (is_not_digit(rgb[i]) == 1)
		{
			printf("Invalid RGB format!.\n");
			free_it((void **)rgb);
			free(color);
			exit(EXIT_FAILURE);
		}

		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Invalid RGB value: %d\n", color[i]);
			free_it((void **)rgb);
			free(color);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (color);
}

int	*set_color_rgb(char *map)
{
	int		*color;
	int		i;
	char	**rgb_code;

	rgb_code = ft_split(map, ',');
	if (!rgb_code)
		return (0);
	i = 0;
	while (rgb_code[i])
		i++;
	if (i != 3)
	{
		printf("Invalid number of RGB components!\n");
		free_it((void **)rgb_code);
		exit(EXIT_FAILURE);
	}
	color = malloc(sizeof(int) * 3);
	if (!color)
	{
		free_it((void **)rgb_code);
		return (0);
	}
	if (!cp_color(rgb_code, color))
	{
		free(color);
		free_it((void **)rgb_code);
		return (0);
	}
	// free_it((void **)rgb_code);
	return (color);
}

int	rgb_codes(t_data *data, char **rgb)
{
	int i;

	i = 0;
	while (rgb[i])
	{
		if (rgb[i][0] == 'C')
		{
			data->texture.rgb_cell = set_color_rgb(rgb[i] + 1);
			if (data->texture.rgb_cell == 0)
				return (error_msg("rgb color error.", 1));
		}
		else if (rgb[i][0] == 'F')
		{
			data->texture.rgb_floor = set_color_rgb(rgb[i] + 1);
			if (data->texture.rgb_floor == 0)
				return (error_msg("rgb color error.", 1));
		}
		else
			return (error_msg("Error!", 1));

		i++;
	}
	return (0);
}

int	set_path(t_map *texture, char **tex_path)
{
	int	i;

	i = 0;
	while (tex_path[i])
	{
		if (tex_path[i][0] == 'W' && tex_path[i][1] == 'E')
			texture->path_texture_west = get_path(tex_path[i], 2);
		else if (tex_path[i][0] == 'S' && tex_path[i][1] == 'O')
			texture->path_texture_south = get_path(tex_path[i], 2);
		else if (tex_path[i][0] == 'E' && tex_path[i][1] == 'A')
			texture->path_texture_east = get_path(tex_path[i], 2);
		else if (tex_path[i][0] == 'N' && tex_path[i][1] == 'O')
			texture->path_texture_north = get_path(tex_path[i], 2);
		else
			return (1);
		i++;
	}
	if (!texture->path_texture_north || !texture->path_texture_east || !texture->path_texture_south
			|| !texture->path_texture_west)
		return (1);
	free_map(tex_path);
	return (0);
}

int	map_data(t_data *data)
{
	if (set_path(&data->map, data->texture.tex_path) == 1)
	{
		free_map(data->texture.tex_path);
		return(error_msg("Failed to get texture path!", 1));
	}
	if (rgb_codes(data, data->texture.rgb_codes) == 1)
	{
		free_map(data->texture.rgb_codes);
		return (error_msg("Failed to get color codes!", 1));
	}
	free_map(data->texture.rgb_codes);
	return (0);
}
