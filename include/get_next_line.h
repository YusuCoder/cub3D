/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:06:36 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/20 16:00:48 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct t_struct
{
	int		new_l_buffer;
	int		fd;
}			t_struct;

t_struct	*get_t_struct(int new_fd);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strjoin_new(char *s1, char *s2);
char		*ft_strndup(char *str, int start, int end);
char		*get_next_line(int fd);
int			new_line(char *str);

#endif
