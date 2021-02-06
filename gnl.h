/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquenten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:03:11 by rquenten          #+#    #+#             */
/*   Updated: 2020/11/16 09:23:29 by rquenten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_line
{
	char	*ptr;
	size_t	len;
	size_t	maxlen;
}				t_line;

typedef struct	s_buffer
{
	char	ptr[BUFFER_SIZE];
	size_t	start;
	size_t	len;
}				t_buffer;

int				get_next_line(int fd, char **line);

#endif
