/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:00:02 by abdsebba          #+#    #+#             */
/*   Updated: 2024/12/15 15:14:17 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

static char	*ft_line(char *tab)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i] != '\n' && tab[i] != '\0')
		i++;
	if (tab[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, tab, i + 1);
	return (line);
}

static char	*ft_next_call(char *buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	new_buffer = ft_substr(buffer, i, ft_strlen(buffer) - i);
	if (new_buffer == NULL || *new_buffer == 0)
	{
		free(new_buffer);
		new_buffer = NULL;
	}
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

static char	*ft_read_buffer(int fd, char *tab)
{
	ssize_t	byte;
	char	*temp;
	char	*place;

	byte = 1;
	place = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (place == NULL)
		return (NULL);
	while (byte > 0)
	{
		byte = read(fd, place, BUFFER_SIZE);
		if (byte < 0)
			return (free(place), NULL);
		if (byte == 0)
			break ;
		place[byte] = '\0';
		temp = tab;
		tab = ft_strjoin(temp, place);
		free(temp);
		temp = NULL;
		if (ft_strchr(place, '\n'))
			break ;
	}
	free(place);
	return (tab);
}

char	*get_next_line(int fd)
{
	static char	*buffer[10240];
	char		*line;

	if (read(fd, 0, 0) < 0 || fd < 0 || fd > 10240
		|| BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
	{
		if (fd <= 10240)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = ft_read_buffer(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_next_call(buffer[fd]);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
