/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:52:54 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/18 16:27:04 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	// check_input(argc, argv);
	// check_map();
	// parse_map();
	init_data(&data);
	run_simulation(&data);
	free_exit(&data, EXIT_SUCCESS);
}
