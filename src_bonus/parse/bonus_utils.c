/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:25:08 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/24 15:26:58 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	is_cub_file(char *str)
{
	size_t	length;

	length = ft_strlen(str);
	if ((str[length - 4] != '.' || str[length - 3] != 'c'
			|| str[length - 2] != 'u' || str[length - 1] != 'b'))
		return (0);
	return (1);
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
