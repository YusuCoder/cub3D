/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:47:13 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/19 13:57:42 by ryusupov         ###   ########.fr       */
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

int	*cp_color(char **rgb, int *color)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		color[i] = ft_atoi(rgb[i]);
		// printf("%d\n", color[i]);
		if (color[i] == -1 || is_not_digit(rgb[i]) == 1)
		{
			free_it((void **)rgb);
			free(color);
			return (0);
		}
		i++;
	}
	// free_it((void **)rgb);
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
		free_it((void **)rgb_code);
		return (0);
	}
	color = malloc(sizeof(int) * 3);
	if (!cp_color(rgb_code, color))
	{
		free(color);
		free_it((void **)rgb_code);
		return (0);
	}
	free_it((void **)rgb_code);
	return (color);
}

int	color_txtures(t_data *data, t_texture *tex_info, char *map, int j)
{
	if (map[j + 1] && !ft_isprint(map[j + 1]))
		return (error_msg(data->map_info.path, "no such file or directory.",
				ERROR));
	if (map[j] == 'C')					//NEEDS TO BE CHECKED WITH MORE COLORS
	{
		tex_info->cell = set_color(map + j + 1);
		if (tex_info->cell == 0)
			return (error_msg(data->map_info.path, "rgb color error.", ERROR));
	}
	else if (!tex_info->floor && map[j] == 'F')
	{
		tex_info->floor = set_color(map + j + 1);
		if (tex_info->floor == 0)
			return (error_msg(data->map_info.path, "rgb color error.", ERROR));
	}
	else
		return (error_msg(data->map_info.path, "Error!", ERROR));
	return (0);
}

int	set_texture_path(t_texture *tex_info, char *map, int j)
{
	// if (map[j + 2] && ft_isprint(map[j + 2]))
	// 	return (1);
	if (map[j] == 'N' && map[j + 1] == 'O' && !(tex_info->north))
		tex_info->north = get_texture(map, j + 2);
	else if (map[j] == 'S' && map[j + 1] == 'O' && !(tex_info->south))
		tex_info->south = get_texture(map, j + 2);
	else if (map[j] == 'E' && map[j + 1] == 'A' && !(tex_info->east))
		tex_info->east = get_texture(map, j + 2);
	else if (map[j] == 'W' && map[j + 1] == 'E' && !(tex_info->west))
		tex_info->west = get_texture(map, j + 2);
	else
		return (1);
	return (0);
}

int	map_check(t_data *data, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1]) && !ft_isdigit(map[i][j])
			&& map[i][j + 1] != ' ')
		{
			if (set_texture_path(&data->tex_info, map[i], j) == 1)
				return (error_msg(data->map_info.path, "invalid texture!", 1));
			return (2);
		}
		else
		{
			if (color_txtures(data, &data->tex_info, map[i], j) == ERROR)
				return (FAIL);
			return (2);
		}
	}
	return (4);
}

int	map_data(t_data *data, char **map)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			res = map_check(data, map, i, j);
			if (res == 2)
				break ;
			else if (res == 1)
				return (1);
			else if (res == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (0);
}
