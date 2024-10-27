/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:54:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/27 15:50:49 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error_msg( char *msg, int exit_code)
{
	ft_putstr_fd("Cub3D: Error!\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (exit_code);
}

void	free_it(void **data)
{
	size_t	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	if (data)
	{
		free(data);
		data = NULL;
	}
}

void	free_it_exit(t_data *data)
{
	printf(RED"Error! Wrong RGB codes!\n"RESET);
	free_map(data->map.map_file);
	free_map(data->texture.tex_path);
	free_path(data);
	exit(EXIT_FAILURE);
}

void	free_map(char **data)
{
	size_t	i;

	i = 0;
	if (data && data[i])
	{
		while (data && data[i])
		{
			free(data[i]);
			i++;
		}
		if (data)
		{
			free(data);
			data = NULL;
		}
	}
}

void	free_and_exit(char **data, t_data *info)
{
	size_t	i;

	i = 0;
	if (data && data[i])
	{
		while (data[i])
		{
			free(data[i]);
			i++;
		}
		if (data)
		{
			free(data);
			data = NULL;
		}
	}
	free_path(info);
	free_color(info);
	exit(EXIT_FAILURE);
}
