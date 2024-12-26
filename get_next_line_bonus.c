/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:24:04 by hajel-ho          #+#    #+#             */
/*   Updated: 2024/12/26 18:07:35 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_it(char **s)
{
	free(*s);
	*s = NULL;
}

char	*check_backup(char **backup )
{
	char	*line;
	char	*temp;
	size_t	count;

	count = 0;
	while (backup[0][count] && backup[0][count] != '\n')
		count++;
	line = ft_substr(backup[0], 0, count + 1);
	temp = *backup;
	*backup = ft_substr(temp, count + 1, ft_strlen(temp) - count);
	if (*backup[0] == '\0')
		free_it(backup);
	free_it(&temp);
	return (line);
}

void	check_buf(char **buf, char **backup, ssize_t read_line)
{
	buf[0][read_line] = '\0';
	if (!*backup)
		backup[0] = ft_strdup("");
	backup[0] = ft_strjoin(backup[0], buf[0]);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*buf;
	ssize_t		read_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (free_it(&buf), free_it(&backup[fd]), NULL);
		else if (read_line == 0)
			break ;
		check_buf(&buf, &backup[fd], read_line);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free_it(&buf);
	if (!backup[fd] || *backup[fd] == '\0')
		return (free_it(&backup[fd]), NULL);
	return (check_backup(&backup[fd]));
}
