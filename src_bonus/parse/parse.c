/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:12:10 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/16 17:05:57 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	line_count(char *argv)
{
	int		fd;
	int		counter;
	char	*line;

	counter = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		error_msg("Failed to open fd!", -1);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			counter++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return(counter);
}

void	validate_map(char *argv, t_data *data)
{
	int	row;
	int	column;
	int	i;

	i = 0;
	row = 0;
	column = 0;
	if ((data->map.line_count = line_count(argv)) == -1)
		exit(EXIT_FAILURE);
	data->map.map_file = ft_calloc(data->map.line_count + 1, sizeof(char *));
	if (!data->map.map_file)
		exit(EXIT_FAILURE);
	data->map.fd = open(argv, O_RDONLY);
	if (data->map.fd < 0)
		exit(EXIT_FAILURE);
	else
	{
		copy_map(row, column, i, data);
		close(data->map.fd);
	}
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

int check_filename(char *arg, int cub)
{
	int fd;

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

void	init_data_parse(t_data *data)
{
	data->map.path_texture_north = NULL;
	data->map.path_texture_south = NULL;
	data->map.path_texture_east = NULL;
	data->map.path_texture_west = NULL;
	data->map.color_ceiling = 0;
	data->map.color_floor = 0;
	data->map.map2d = NULL;
}

int	parse(t_data *data, char **argv)
{
	init_data_parse(data);
	if (check_filename(argv[1], 1) == 1)
		return(1);
	validate_map(argv[1], data);
	extract_path(data);
	extract_color(data);
	extract_map(data);
	filter_map(data);
	if (map_data(data) == 1)
		exit(EXIT_FAILURE);
	check_components(data);
	check_walls(data);
	get_player_dir(data);
	return (0);
}
