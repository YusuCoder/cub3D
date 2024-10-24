/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_sizeof_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:53:52 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/24 15:45:40 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_next_line_length(char **map, int i, int len)
{
	int	next_len;

	next_len = 0;
	while (map[i + 1][next_len] && map[i + 1][next_len] != '\n')
		next_len++;
	if (next_len > len)
	{
		while (map[i + 1][len] && map[i + 1][len] != '\n')
		{
			if (map[i + 1][len] == '0')
				return (1);
			len++;
		}
	}
	return (0);
}

static int	check_next_line_below(char **map, int i, int next_len)
{
	int	len_below;

	len_below = 0;
	if (map[i + 2])
	{
		while (map[i + 2][len_below] && map[i + 2][len_below] != '\n')
			len_below++;
	}
	if (map[i + 2] && next_len > len_below)
	{
		while (map[i + 1][len_below] && map[i + 1][len_below] != '\n')
		{
			if (map[i + 1][len_below] == '0')
				return (1);
			len_below++;
		}
	}
	return (0);
}

int	size_of_lines(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i + 1])
	{
		len = 0;
		while (map[i][len] && map[i][len] != '\n')
			len++;
		if (check_next_line_length(map, i, len))
			return (1);
		if (check_next_line_below(map, i, len))
			return (1);
		i++;
	}
	return (0);
}
