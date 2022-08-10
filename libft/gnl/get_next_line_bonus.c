/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 11:12:48 by jhille        #+#    #+#                 */
/*   Updated: 2021/11/21 23:03:30 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

static int	reststore(int fd, char *store[], char *line, int i)
{
	char	*temp;

	if (store[fd] == 0)
	{
		store[fd] = gnl_substr(line, i, linelen(line, 2));
		if (store[fd] == 0)
			return (-1);
		else
			return (1);
	}
	if (i > 0)
		temp = gnl_substr(line, i, linelen(line, 2) - i);
	else
		temp = gnl_substr(store[fd], i * -1, linelen(store[fd], 2) - (i * -1));
	free(store[fd]);
	if (temp == 0)
		return (-1);
	store[fd] = temp;
	return (1);
}

static int	readloop(int fd, char *buf, char *store[fd], char **line)
{
	int		ret;
	char	*temp;

	ret = -20;
	while (linelen(*line, 0) == 2 && ret != 0)
	{
		ft_setzero(buf, BUFFER_SIZE + 1);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		if ((buf[0] == '\n' && BUFFER_SIZE == 1) || ret == 0)
			break ;
		temp = ft_gnl_strjoin(*line, buf);
		free(*line);
		*line = temp;
		if (*line == 0)
			return (-1);
	}
	if (linelen(*line, 0) == 1)
		ret = reststore(fd, store, *line, linelen(*line, 1) + 1);
	else if ((linelen(*line, 2) > 0) && (ret != 0 && ret != -1))
		ret = 1;
	if (ret == -1)
		return (-1);
	return (ret);
}

static int	finishline(int fd, char *buf, char *store[], char **line)
{
	int		i;
	int		ret;
	char	*temp;

	ret = 1;
	*line = gnl_substr(store[fd], 0, linelen(store[fd], 1));
	if (*line == 0)
		return (-1);
	i = linelen(store[fd], 0);
	if (i == 2 && store[fd][0] != '\n')
		ret = readloop(fd, buf, store, line);
	else if (i == 1)
		ret = reststore(fd, store, *line, (linelen(store[fd], 1) + 1) * -1);
	if ((i == 0 || i != 1) && (linelen(*line, 0) != 1) && (ret != -1))
	{
		free(store[fd]);
		store[fd] = 0;
	}
	if (linelen(*line, 0) != 2 && ret != -1)
	{
		temp = gnl_substr(*line, 0, linelen(*line, 1));
		free(*line);
		*line = temp;
	}
	return (ret);
}

static int	writeline(int fd, char *buf, char *store[], char **line)
{
	int		ret;
	char	*temp;

	ret = 1;
	if (buf[0] == '\0')
		*line = ft_gnl_calloc(1, 1);
	else
		*line = gnl_substr(buf, 0, linelen(buf, 1));
	if (*line == 0)
		return (-1);
	if (linelen(buf, 0) == 2 && ret != 0)
	{
		ret = readloop(fd, buf, store, line);
		if ((ret != -1) && (linelen(*line, 0) == 0 || 1))
		{
			temp = gnl_substr(*line, 0, linelen(*line, 1));
			free(*line);
			*line = temp;
		}
	}
	else if (linelen(buf, 0) == 1 && ret != 0)
		ret = reststore(fd, store, buf, linelen(buf, 1) + 1);
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char	*store[MAX_FD];
	char		*buf;

	ret = 0;
	buf = ft_gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (line == 0 || fd > MAX_FD || fd < 0 || BUFFER_SIZE < 1 || buf == 0)
		ret = -1;
	if (store[fd] == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret != 0 && ret != -1)
			ret = writeline(fd, buf, store, line);
		else
			*line = ft_gnl_calloc(1, 1);
	}
	else if (ret != -1)
		ret = finishline(fd, buf, store, line);
	if (ret == -1 && store[fd] != 0)
		free(store[fd]);
	if (buf != 0)
		free(buf);
	if (ret != -1 && *line == 0)
		ret = -1;
	return (ret);
}
