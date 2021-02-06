/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquenten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:53:11 by rquenten          #+#    #+#             */
/*   Updated: 2020/11/16 09:20:06 by rquenten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	line_new(t_buffer *buff)
{
	int res;

	res = 0;
	if (buff->start < buff->len)
	{
		buff->ptr[buff->start] = '\n';
		res = buff->ptr[buff->start];
	}
	return (res);
}

static int	line_broaden(t_line *line, size_t necessary)
{
	char	*newptr;
	size_t	new_maxlen;
	size_t	i;

	if (line->maxlen)
		new_maxlen = (line->maxlen);
	else
		new_maxlen = 32;
	while (new_maxlen < necessary)
		new_maxlen *= 2;
	newptr = (char *)malloc(new_maxlen + 1);
	if (newptr)
	{
		i = -1;
		while (++i < (size_t)line->len)
			newptr[i] = line->ptr[i];
		if (line->ptr)
			free(line->ptr);
		line->ptr = newptr;
		line->maxlen = new_maxlen;
		line->ptr[line->len] = '\0';
	}
	return (newptr != NULL);
}

static int	line_add(t_line *line, t_buffer *buff)
{
	char	*newptr;
	size_t	newlen;
	size_t	len;
	size_t	i;

	i = 1;
	if (buff->start <= buff->len)
	{
		newptr = buff->ptr + buff->start;
		newlen = buff->len - buff->start;
		len = 0;
		while (len < newlen && newptr[len] != '\n')
			len++;
		if (!line->maxlen || line->maxlen - line->len < len)
			i = line_broaden(line, line->len + len);
		if (i)
		{
			len = 0;
			while (len < newlen && newptr[len] != '\n')
				line->ptr[line->len++] = newptr[len++];
			line->ptr[line->len] = '\0';
			buff->start += len;
		}
	}
	return (i);
}

static int	line_read(t_line *line, t_buffer *buff, int fd)
{
	ssize_t res;

	line->len = 0;
	res = line_add(line, buff);
	while (res > 0 && !line_new(buff))
	{
		res = read(fd, buff->ptr, BUFFER_SIZE);
		if (res > 0)
		{
			buff->start = 0;
			buff->len = res;
			if (line_add(line, buff))
				res = 1;
			else
				res = -1;
		}
	}
	if (line_new(buff))
	{
		if (!res && line->len > 0)
			res = 1;
		buff->start++;
	}
	return (res);
}

int			get_next_line(int fd, char **line)
{
	static t_buffer	buff;
	t_line			newline;
	int				res;

	newline.maxlen = 0;
	newline.ptr = NULL;
	res = line_read(&newline, &buff, fd);
	*line = 0;
	if (res >= 0)
		*line = newline.ptr;
	else if (newline.ptr)
		free(newline.ptr);
	return (res);
}
