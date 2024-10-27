/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:20:11 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/27 16:23:45 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_not_digit(char *str)
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
			return (0);
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			free(color);
			return (0);
		}
		i++;
	}
	return (color);
}
