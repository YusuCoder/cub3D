/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:49:19 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/12 21:15:18 by tkubanyc         ###   ########.fr       */
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

void	delete_textures(t_texture *texture)
{
	if (texture->north != NULL)
	{
		mlx_delete_texture(texture->north);
		texture->north = NULL;
	}
	if (texture->south != NULL)
	{
		mlx_delete_texture(texture->south);
		texture->south = NULL;
	}
	if (texture->east != NULL)
	{
		mlx_delete_texture(texture->east);
		texture->east = NULL;
	}
	if (texture->west != NULL)
	{
		mlx_delete_texture(texture->west);
		texture->west = NULL;
	}
}

void	delete_weapon(mlx_t *mlx, mlx_image_t *weapon[], int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (weapon[i] != NULL)
		{
			mlx_delete_image(mlx, weapon[i]);
			weapon[i] = NULL;
		}
		i++;
	}
}

void	delete_sprites(t_sprite *sprite, mlx_t *mlx)
{
	if (sprite->aim != NULL)
	{
		mlx_delete_image(mlx, sprite->aim);
		sprite->aim = NULL;
	}
	delete_weapon(mlx, sprite->rifle, 6);
	delete_weapon(mlx, sprite->bullet, 6);
	delete_weapon(mlx, sprite->pistol, 9);
	delete_weapon(mlx, sprite->knife, 7);
}

void	free_exit(t_data *data, int exit_status)
{
	mlx_close_window(data->mlx);
	if (data->img != NULL)
	mlx_delete_image(data->mlx, data->img);
	if (data->buf != NULL)
		mlx_delete_image(data->mlx, data->buf);
	delete_textures(&data->texture);
	delete_sprites(&data->sprite, data->mlx);
	mlx_terminate(data->mlx);
	if (data->map.map2d != NULL)
		free_array(data->map.map2d);
	exit(exit_status);
}
