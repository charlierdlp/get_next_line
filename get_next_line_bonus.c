/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:53:33 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/24 19:11:35 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"
#include <fcntl.h>

int	ft_separator(char **content, char **line, int fd)
{
	char	*tmp;
	int		i;
	int		j;

	if (!content[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!ft_strchr(content[fd], '\n'))
	{
		*line = ft_strdup(content[fd]);
		free(content[fd]);
		content[fd] = NULL;
		return (0);
	}
	i = ft_strlen(content[fd]);
	j = ft_strlen(ft_strchr(content[fd], '\n'));
	*line = ft_substr(content[fd], 0, i - j);
	tmp = content[fd];
	content[fd] = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	return (1);
}

void	alloc_content(char **content, char *buf, int i, int fd)
{
	char	*tmp;

	buf[i] = '\0';
	if (!content[fd])
		content[fd] = ft_strdup(buf);
	else
	{
		tmp = content[fd];
		content[fd] = ft_strjoin(content[fd], buf);
		free(tmp);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*content[4096];
	char		*buf;
	int			i;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd == -1 || BUFFER_SIZE < 1 || read(fd, buf, 0) == -1
		|| !line || !buf)
		return (-1);
	if (!(content[fd] && ft_strchr(content[fd], '\n')))
	{	
		i = read(fd, buf, BUFFER_SIZE);
		while (i > 0)
		{
			alloc_content(content, buf, i, fd);
			if (ft_strchr(buf, '\n'))
				break ;
			i = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
	return (ft_separator(content, line, fd));
}
