/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:21:11 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/27 16:38:14 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	extract_map(t_data *data)
{
	int	i;
	int	k;

	i = 0;
	while (data->map_info.map[i][0] != '1' && data->map_info.map[i][0] != '0')
		i++;
	data->map_info.map2d = (char **)malloc(sizeof(char *) * (data->height + 1));
	if (!data->map_info.map2d)
		exit(EXIT_FAILURE);
	k = 0;
	while (data->map_info.map[i])
	{
		data->map_info.map2d[k] = ft_strdup(data->map_info.map[i]);
		if (!data->map_info.map2d[k])
		{
			while (--k >= 0)
				free(data->map_info.map2d[k]);
			free(data->map_info.map2d);
			exit(EXIT_FAILURE);
		}
		i++;
		k++;
	}
	data->map_info.map2d[k] = NULL;
}

int	is_cub_file(char *str)
{
	size_t	length;

	length = ft_strlen(str);
	if ((str[length - 4] != '.' || str[length - 3] != 'c' || str[length
			- 2] != 'u' || str[length - 1] != 'b'))
		return (0);
	return (1);
}

int	is_dir(char *str)
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

int	check_file(char *arg, int cub)
{
	int	fd;

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

void	init_map(t_data *data)
{
	data->tex_info.north = NULL;
	data->tex_info.south = NULL;
	data->tex_info.west = NULL;
	data->tex_info.east = NULL;
}

int	parse(t_data *data, char **argv)
{
	init_map(data);
	if (check_file(argv[1], 1) == FAIL)
		exit(FAIL);
	// clean_exit(data, FAIL);
	validate_map(argv[1], data);
	if (map_data(data, data->map_info.map) == FAIL)
		exit(EXIT_FAILURE);
	extract_map(data);
	// int i, j;
	// i = 0;
	// while (data->map_info.map2d[i])
	// {
	// 	j = 0;
	// 	while (data->map_info.map2d[i][j])
	// 	{
	// 		printf("[%c]", data->map_info.map2d[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	check_map_contents(data, data->map_info.map2d);
		//NEED TO REPLACE WITH FREE FUNCTION
	return (0);
}
