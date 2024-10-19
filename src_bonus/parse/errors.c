/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:54:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/16 17:06:43 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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
void	free_map(char **data)
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

void	free_and_exit(char **data)
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
	exit(EXIT_FAILURE);
}