/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:49:19 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/29 19:25:00 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*-----------------*/
/*  Free 2D array  */
/*-----------------*/
void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_exit(t_data *data, int exit_status)
{
	mlx_close_window(data->mlx);
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	if (data->buf != NULL)
		mlx_delete_image(data->mlx, data->buf);
	if (data->texture.north != NULL)
		mlx_delete_texture(data->texture.north);
	if (data->texture.south != NULL)
		mlx_delete_texture(data->texture.south);
	if (data->texture.east != NULL)
		mlx_delete_texture(data->texture.east);
	if (data->texture.west != NULL)
		mlx_delete_texture(data->texture.west);
	if (data->mlx != NULL)
		mlx_terminate(data->mlx);
	if (data != NULL)
	{
		if (data->map.map2d != NULL)
			free_array(data->map.map2d);
	}
	exit(exit_status);
}
