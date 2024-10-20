/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:39:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/19 17:39:08 by ryusupov         ###   ########.fr       */
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

	if (access("src_bonus/sound_handling/sounds/move_garvel.mp3", F_OK) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("afplay", "afplay", "-v", "0.9", "src_bonus/sound_handling/sounds/move_garvel.mp3", (char *)NULL);
			_exit(1);
		}
		return (pid);
	}
	else
	{
		printf("The file 'assets/move4.mp3' does not exist.\n");
		return (-1);
	}
}

void	door_sound(t_data *data)
{
	pid_t pid;

	(void)data;
	if (access("src_bonus/sound_handling/sounds/door.mp3", F_OK) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("afplay", "afplay", "-v", "0.5", "src_bonus/sound_handling/sounds/door.mp3", (char *)NULL);
			_exit(1);
		}
	}
	else
		printf("The file move1.mp3 not found!\n");
}

void	gun_sound(void)
{
	pid_t pid;

	if (access("src_bonus/sound_handling/sounds/pistol.mp3", F_OK) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("afplay", "afplay", "-v", "0.7", "src_bonus/sound_handling/sounds/pistol.mp3", (char *)NULL);
			_exit(1);
		}
	}
	else
		printf("The file move1.mp3 not found!\n");
}

void	rifle_sound(void)
{
	pid_t pid;

	if (access("src_bonus/sound_handling/sounds/gun_shot.mp3", F_OK) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("afplay", "afplay", "-v", "0.7", "src_bonus/sound_handling/sounds/gun_shot.mp3", (char *)NULL);
			_exit(1);
		}
	}
	else
		printf("The file move1.mp3 not found!\n");
}

void	knife_sound(void)
{
	pid_t pid;

	if (access("src_bonus/sound_handling/sounds/knife.mp3", F_OK) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("afplay", "afplay", "-v", "0.7", "src_bonus/sound_handling/sounds/knife.mp3", (char *)NULL);
			_exit(1);
		}
	}
	else
		printf("The file move1.mp3 not found!\n");
}
