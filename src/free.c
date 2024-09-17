/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:49:19 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/17 12:45:52 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	free_exit(t_data *data)
{
	mlx_close_window(data->mlx);
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx != NULL)
		mlx_terminate(data->mlx);
	if (data->map.map2d != NULL)
		free_array(data->map.map2d);
	if (data != NULL)
		data = NULL;
	exit(EXIT_SUCCESS);
}
