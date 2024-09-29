/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:47:13 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/29 21:08:29 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	*set_color(char *map)
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

int	color_txtures(t_data *data, char **rgb)
{
	int i;

	i = 0;
	while (rgb[i])
	{
		if (rgb[i][0] == 'C')
		{
			data->tex_info.cell = set_color(rgb[i] + 1);
			if (data->tex_info.cell == 0)
				return (error_msg(data->map_info.path, "rgb color error.", ERROR));
		}
		else if (!data->tex_info.floor && rgb[i][0] == 'F')
		{
			data->tex_info.floor = set_color(rgb[i] + 1);
			if (data->tex_info.floor == 0)
				return (error_msg(data->map_info.path, "rgb color error.", ERROR));
		}
		else
			return (error_msg(data->map_info.path, "Error!", ERROR));

		i++;
	}
	return (0);
}


char	*get_texture(char *map, int j)
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

int	set_texture_path(t_texture *tex_info, char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'W' && map[i][1] == 'E')
			tex_info->north = get_texture(map[i], 2);
		else if (map[i][0] == 'S' && map[i][1] == 'O')
			tex_info->south = get_texture(map[i], 2);
		else if (map[i][0] == 'E' && map[i][1] == 'A')
			tex_info->east = get_texture(map[i], 2);
		else if (map[i][0] == 'N' && map[i][1] == 'O')
			tex_info->west = get_texture(map[i], 2);
		else
			return (1);
		i++;
	}
	if (!tex_info->north || !tex_info->south || !tex_info->east || !tex_info->west)
		return (1);
	return (0);
}

int	map_data(t_data *data)
{
	int	i;

	i = 0;
	if (set_texture_path(&data->tex_info, data->tex_info.tex_path) == 1)
		return (error_msg(data->map_info.path, "invalid texture!", 1));
	if (color_txtures(data, data->tex_info.rgb_codes) == 1)
		return (error_msg(data->map_info.path, "invalid rgb_code!", 1));
	return (0);
}
