/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:52:54 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/13 12:12:04 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int argc, char **argv)
{

	t_data data;

	if (argc != 2)
	{
		printf("Error!\n");
		return (-1);
	}
	if (parse(&data, argv) != 0)
		return (1);
	printf("Hello. This is 🎮 cub3D\n");
	return (0);
}
