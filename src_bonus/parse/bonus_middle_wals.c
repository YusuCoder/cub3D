/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_middle_wals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:56:30 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/26 16:00:20 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_horizontal(char **map, int i, int j)
{
	if ((map[i][j] == '0' && ft_strchr(" \t", map[i][j + 1]) != NULL)
		|| (map[i][j] == '0' && ft_strchr(" \t", map[i][j - 1]) != NULL))
		return (1);
	return (0);
}

static int	check_vertical(char **map, int i, int j)
{
	if ((map[i][j] == '0'
		&& ft_strchr(" \t", map[i - 1][j]) != NULL)
		|| (map[i][j] == '0'
		&& map[i + 1] != NULL && ft_strchr(" \t", map[i + 1][j]) != NULL))
		return (1);
	return (0);
}

static int	check_last_line(char **map, int i, int j)
{
	if (map[i + 1] == NULL)
	{
		if ((ft_strchr(" \t", map[i][j]) && map[i - 1][j] == '0'))
			return (1);
	}
	return (0);
}

static int	check_doors(char **map, int i, int j)
{
	if ((map[i][j] == '2'
		&& ft_strchr(" \t", map[i - 1][j]) != NULL)
		|| (map[i][j] == '2'
		&& map[i + 1] != NULL && ft_strchr(" \t", map[i + 1][j]) != NULL))
		return (1);
	return (0);
}

int	middle_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_horizontal(map, i, j))
				return (1);
			if (check_vertical(map, i, j))
				return (1);
			if (check_last_line(map, i, j))
				return (1);
			if (check_doors(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
