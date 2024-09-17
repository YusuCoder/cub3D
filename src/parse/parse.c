/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:21:11 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/17 13:52:46 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_cub_file(char *str)
{
	size_t	length;

	length = ft_strlen(str);
	if ((str[length - 4] != '.' || str[length - 3] != 'c'
			|| str[length - 2] != 'u' || str[length - 1] != 'b'))
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
		close (fd);
		res = 1;
	}
	return (res);
}

int	check_file(char	*arg, int cub)
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

int	parse(t_data *data, char **argv)
{
	(void)data;
	if (check_file(argv[1], 1) == FAIL)
		exit(FAIL);
		// clean_exit(data, FAIL);
	validate_map(argv[1], data);
	// int i, j;
	// i = 0;
	// j = 0;
	// while (data->map_info.map[i] != NULL)
	// {
	// 	j = 0;
	// 	while (data->map_info.map[i][j] != '\0')
	// 	{
	// 		printf("%c", data->map_info.map[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	if (map_data(data, data->map_info.map) == FAIL)
		exit(EXIT_FAILURE);							//NEED TO REPLACE WITH FREE FUNCTION
	printf("%s\n", data->tex_info.south);
	printf("%s\n", data->tex_info.north);
	printf("%s\n", data->tex_info.west);
	printf("%s\n", data->tex_info.east); 							
	return (0);
}
