/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:39:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/26 14:27:44 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	play_sound(pthread_t *thread, void *(*play)(void *))
{
	pthread_create(thread, NULL, play, NULL);
	pthread_detach(*thread);
}

void	game_over(void)
{
	pid_t	pid;

	if (access("src_bonus/sound_handling/sounds/demon.mp3", F_OK) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("afplay", "afplay", "-v", "0.7", \
				"src_bonus/sound_handling/sounds/demon.mp3", (char *) NULL);
			_exit(1);
		}
	}
	else
		printf("The file move1.mp3 not found!\n");
}
