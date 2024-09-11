/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:39:27 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/11 13:45:13 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_perror(char *error_msg)
{
	write(2, "Error\n", 6);
	if (error_msg != NULL)
	{
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
	}
}

void	error_exit(t_data *data)
{
	ft_perror(NULL);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	mlx_close_window(data->mlx);
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx != NULL)
		mlx_terminate(data->mlx);
	if (data != NULL)
		data = NULL;
	exit(EXIT_FAILURE);
}
