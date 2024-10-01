/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:21:11 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/01 12:08:16 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	extract_color(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->tex_info.rgb_codes = (char **)malloc(sizeof(char *) * 3);
	if (!data->tex_info.rgb_codes)
		exit(EXIT_FAILURE);
	while (data->map_info.map[i] && j < 3)
	{
		if (ft_strncmp(data->map_info.map[i], "F", 1) == 0 ||
			ft_strncmp(data->map_info.map[i], "C", 1) == 0)
		{
			data->tex_info.rgb_codes[j] = ft_strdup(data->map_info.map[i]);
			if (!data->tex_info.rgb_codes[j])
			{
				while (--j >= 0)
					free(data->tex_info.rgb_codes[j]);
				free(data->tex_info.rgb_codes);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	data->tex_info.rgb_codes[j] = NULL;
}

void	extract_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->tex_info.tex_path = (char **)malloc(sizeof(char *) * 5);
	if (!data->tex_info.tex_path)
		exit(EXIT_FAILURE);

	while (data->map_info.map[i] && j < 4)
	{
		if (ft_strncmp(data->map_info.map[i], "NO", 2) == 0 ||
			ft_strncmp(data->map_info.map[i], "SO", 2) == 0 ||
			ft_strncmp(data->map_info.map[i], "EA", 2) == 0 ||
			ft_strncmp(data->map_info.map[i], "WE", 2) == 0)
		{
			data->tex_info.tex_path[j] = ft_strdup(data->map_info.map[i]);
			if (!data->tex_info.tex_path[j])
			{
				while (--j >= 0)
					free(data->tex_info.tex_path[j]);
				free(data->tex_info.tex_path);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
		// if (j == 4)
		// 	break;
	}
	data->tex_info.tex_path[j] = NULL;
}

void extract_map(t_map *data)
{
	int i;
	int k;
	i = 0;
	k = 0;
	while (data->map[i] && !strchr(data->map[i], '1') && !strchr(data->map[i], '0'))
		i++;
	data->map2d = (char **)malloc(sizeof(char *) * (data->height + 1));
	if (!data->map2d)
		exit(EXIT_FAILURE);
	k = 0;
	while (data->map[i])
	{
		data->map2d[k] = ft_strdup(data->map[i]);
		if (!data->map2d[k])
		{
			while (--k >= 0)
				free(data->map2d[k]);
			free(data->map2d);
			exit(EXIT_FAILURE);
		}
		i++;
		k++;
	}
	data->map2d[k] = NULL;
}


int is_cub_file(char *str)
{
	size_t length;

	length = ft_strlen(str);
	if ((str[length - 4] != '.' || str[length - 3] != 'c' || str[length - 2] != 'u' || str[length - 1] != 'b'))
		return (0);
	return (1);
}

int is_dir(char *str)
{
	int fd;
	int res;

	res = 0;
	fd = open(str, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		res = 1;
	}
	return (res);
}

int check_file(char *arg, int cub)
{
	int fd;

	if (is_dir(arg))
		return (error_msg(arg, "is directory", FAIL));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (error_msg(arg, "open error!\n", FAIL));
	close(fd);
	if (cub && !is_cub_file(arg))
		return (error_msg(arg, "File is not .cub\n", FAIL));
	return (SUCCESS);
}

void init_map(t_data *data)
{
	data->tex_info.north = NULL;
	data->tex_info.south = NULL;
	data->tex_info.west = NULL;
	data->tex_info.east = NULL;
	data->tex_info.cell = NULL;
	data->tex_info.floor = NULL;
}

int parse(t_data *data, char **argv)
{
	init_map(data);
	if (check_file(argv[1], 1) == FAIL)
		exit(FAIL);
	// clean_exit(data, FAIL);
	validate_map(argv[1], data);
	extract_path(data);
	extract_color(data);
	if (map_data(data) == FAIL)
		exit(EXIT_FAILURE);
	check_map_contents(data, data->map_info.map2d);
	return (0);
}
