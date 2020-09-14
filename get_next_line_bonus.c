/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:53:33 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/02/11 16:34:55 by cruiz-de         ###   ########.fr       */
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

int	get_next_line(int fd, char **line)
{
	static char	*content[4096];
	char		*tmp;
	char		*buf;
	int			i;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (fd == -1 || BUFFER_SIZE < 1 || read(fd, buf, 0) == -1 || line == NULL)
		return (-1);
	while ((i = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!content[fd])
			content[fd] = ft_strdup(buf);
		else
		{
			tmp = content[fd];
			content[fd] = ft_strjoin(content[fd], buf);
			free(tmp);
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (ft_separator(content, line, fd));
}
