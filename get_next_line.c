/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-sch <rvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 21:04:36 by rvan-sch      #+#    #+#                 */
/*   Updated: 2020/01/20 17:53:54 by rvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	buff_move(char *s, int start, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		s[i] = s[start + i];
		i++;
	}
	while (s[i])
	{
		s[i] = '\0';
		i++;
	}
}

static int	buff_exists(char *buff, char **line)
{
	char *tmp;

	buff_move(buff, 1, BUFFER_SIZE - 1);
	tmp = ft_substr(buff, 0, amount_char(buff));
	if (!tmp)
		return (-1);
	*line = ft_strjoin(*line, tmp);
	free(tmp);
	if (!line)
		return (-1);
	buff_move(buff, amount_char(buff), BUFFER_SIZE - amount_char(buff));
	if (buff[0] == '\n')
		return (1);
	return (0);
}

static int	fill_line(char *buff, char **line)
{
	char *tmp;

	tmp = ft_substr(buff, 0, amount_char(buff));
	if (!tmp)
		return (-1);
	*line = ft_strjoin(*line, tmp);
	free(tmp);
	if (!line)
		return (-1);
	return (0);
}

static int	ft_init(int fd, char **line, char *buff)
{
	int ret;

	if (!line || BUFFER_SIZE < 1 || fd < 0 || fd >= OPEN_MAX ||
			(read(fd, 0, 0) < 0))
		return (-1);
	*line = ft_strdup("");
	if (*line == NULL)
		return (-1);
	if (buff[0] == '\n')
	{
		ret = buff_exists(buff, line);
		if (ret > 0)
			return (1);
		else if (ret == -1)
			return (-1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	int			ret;

	ret = ft_init(fd, line, buff[fd]);
	if (ret == 1 || ret == -1)
		return (ret);
	ret = read(fd, buff[fd], BUFFER_SIZE);
	while (ret > 0)
	{
		if (fill_line(buff[fd], line) == -1)
			return (-1);
		if (amount_char(buff[fd]) < BUFFER_SIZE)
		{
			buff_move(buff[fd], amount_char(buff[fd]),
					BUFFER_SIZE - amount_char(buff[fd]));
			if (buff[fd][0] == 0)
				return (0);
			return (1);
		}
		buff_move(buff[fd], 0, 0);
		ret = read(fd, buff[fd], BUFFER_SIZE);
	}
	if (ret == -1)
		return (-1);
	return (0);
}
