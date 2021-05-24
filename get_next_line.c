/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:53:33 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/24 19:01:44 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_separator(char **content, char **line)
{
	char	*tmp;
	int		i;
	int		j;

	if (!*content)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!ft_strchr(*content, '\n'))
	{
		*line = ft_strdup(*content);
		free(*content);
		*content = NULL;
		return (0);
	}
	i = ft_strlen(*content);
	j = ft_strlen(ft_strchr(*content, '\n'));
	*line = ft_substr(*content, 0, i - j);
	tmp = *content;
	*content = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	return (1);
}

void	alloc_content(char **content, char *buf, int i)
{
	char	*tmp;

	buf[i] = '\0';
	if (!*content)
		*content = ft_strdup(buf);
	else
	{
		tmp = *content;
		*content = ft_strjoin(*content, buf);
		free(tmp);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*content;
	char		*buf;
	int			i;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd == -1 || BUFFER_SIZE < 1 || read(fd, buf, 0) == -1
		|| !line || !buf)
		return (-1);
	if (!(content && ft_strchr(content, '\n')))
	{
		i = read(fd, buf, BUFFER_SIZE);
		while (i > 0)
		{
			alloc_content(&content, buf, i);
			if (ft_strchr(buf, '\n'))
				break ;
			i = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
	return (ft_separator(&content, line));
}
