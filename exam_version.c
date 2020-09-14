/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encore.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:13:04 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/07/23 12:08:53 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

char *ft_strchr(char *str, char c)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return(&str[i]);
		i++;
	}
	if (str[i] == c)
		return(&str[i]);
	return(0);
}

char *ft_substr(char *str, int start, int len)
{
	char *new;
	int i = 0;

	if(!(new = malloc(len + 1)))
		return(NULL);
	while(i < len)
	{
		new[i] = str[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return(new);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *new;
	int i = 0;
	int j = 0;

	if(!(new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return(NULL);
	while(s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while(s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return(new);
}

char *ft_strdup(char *str)
{
	char *new;
	int i = 0;

	if(!(new = malloc(ft_strlen(str) + 1)))
		return(NULL);
	while(str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return(new);
}

int ft_separator(char **content, char **line)
{
	int i;
	int j;
	char *tmp;

	if(!*content)
	{
		*line = ft_strdup("");
		return(0);
	}
	if (!ft_strchr(*content, '\n'))
	{
		*line = ft_strdup(*content);
		free(*content);
		*content = NULL;
		return(0);
	}
	i = ft_strlen(*content);
	j = ft_strlen(ft_strchr(*content, '\n'));
	*line = ft_substr(*content, 0, i-j);
	tmp = *content;
	*content = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	return(1);
}

int get_next_line(char **line)
{
	int i;
	char *tmp;
	char *buf;
	static char *content;

	if(!(buf = malloc(BUFFER_SIZE + 1)))
		return(-1);
	if (read(0, buf, 0) == -1 || line == NULL)
		return(-1);
	if (content && ft_strchr(content, '\n'))
	{
		free(buf);
		return(ft_separator(&content, line));
	}
	
	while((i = read(0, buf, BUFFER_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!content)
			content = ft_strdup(buf);
		else
		{
			tmp = content;
			content = ft_strjoin(content, buf);
			free(tmp);
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return(ft_separator(&content, line));
}

int main()
{
	int i = 1;
	char *line;

	while(i == 1)
	{
		i = get_next_line(&line);
		printf("%s\n", line);
		free(line);
	}
	system("leaks a.out");
}
