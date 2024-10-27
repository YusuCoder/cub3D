/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:07:18 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/26 20:51:27 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_color(t_data *data)
{
	if (data->texture.rgb_cell != NULL)
		free(data->texture.rgb_cell);
	if (data->texture.rgb_floor != NULL)
		free(data->texture.rgb_floor);
}

void	free_path(t_data *data)
{
	if (data->map.path_texture_north != NULL)
	{
		free(data->map.path_texture_north);
		data->map.path_texture_north = NULL;
	}
	if (data->map.path_texture_east != NULL)
	{
		free(data->map.path_texture_east);
		data->map.path_texture_east = NULL;
	}
	if (data->map.path_texture_west != NULL)
	{
		free(data->map.path_texture_west);
		data->map.path_texture_west = NULL;
	}
	if (data->map.path_texture_south != NULL)
	{
		free(data->map.path_texture_south);
		data->map.path_texture_south = NULL;
	}
}

static int	is_dir(char *str)
{
	int	fd;
	int	res;

	res = 0;
	fd = open(str, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		res = 1;
	}
	return (res);
}

static int	is_cub_file(char *str)
{
	size_t	length;

	length = ft_strlen(str);
	if ((str[length - 4] != '.' || str[length - 3] != 'c'
			|| str[length - 2] != 'u' || str[length - 1] != 'b'))
		return (0);
	return (1);
}

int	check_filename(char *arg, int cub)
{
	int	fd;

	if (is_dir(arg))
		return (error_msg("is directory", 1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (error_msg("open error!", 1));
	close(fd);
	if (cub && !is_cub_file(arg))
		return (error_msg("File is not .cub", 1));
	return (0);
}
