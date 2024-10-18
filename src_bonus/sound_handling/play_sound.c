/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:39:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/18 18:48:48 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	play_sound(pthread_t *thread, void *(*play)(void *))
{
	pthread_create(thread, NULL, play, NULL);
	pthread_detach(*thread);
}

pid_t player_move_sound(void)
{
	pid_t pid;

	if (access("src_bonus/sound_handling/sounds/move.mp3", F_OK) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("afplay", "afplay", "-v", "0.9", "src_bonus/sound_handling/sounds/move.mp3", (char *)NULL);
			_exit(1);
		}
		return pid;
	}
	else
	{
		printf("The file 'assets/move.mp3' does not exist.\n");
		return -1;
	}
}


// void *player_move_sound(void *arg)
// {
// 	(void)arg;
// 	if (access("src_bonus/sound_handling/sounds/move1.mp3", F_OK) != -1)
// 	{
// 		if (fork() == 0)
// 		{
// 			execlp("afplay", "afplay", "-v", "0.1", "src_bonus/sound_handling/sounds/move1.mp3", (char *)NULL);
// 			_exit(1);
// 		}
// 	}
// 	else
// 		printf("The file 'assets/move.mp3' does not exist.\n");
// 	return NULL;
// }
