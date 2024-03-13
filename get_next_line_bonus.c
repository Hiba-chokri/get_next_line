/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:44 by hichokri          #+#    #+#             */
/*   Updated: 2024/01/14 10:02:45 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_lines(int fd, char *arr)
{
	char	*buffer;
	int		r_bytes;

	buffer = malloc(((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	r_bytes = 1;
	while (!ft_strchr(arr, '\n') && r_bytes != 0)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			free(arr);
			free(buffer);
			return (NULL);
		}
		buffer[r_bytes] = '\0';
		arr = ft_strjoin(arr, buffer);
	}
	free(buffer);
	if (r_bytes == 0 && (!arr || arr[0] == '\0'))
		return (free(arr), NULL);
	return (arr);
}

char	*current_line(char *buffer)
{
	char	*current;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	current = malloc((i + 1) * sizeof(char));
	if (!current)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		current[i++] = buffer[j++];
	if (buffer[i] == '\n')
		current[i++] = buffer[j];
	current[i] = '\0';
	return (current);
}

char	*next_line(char *buffer)
{
	char	*next;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	next = malloc((ft_strlen(buffer) - i) * sizeof(char));
	if (!next)
		return (NULL);
	if (buffer[i] == '\n')
		i++;
	while (buffer[i] != '\0')
		next[j++] = buffer[i++];
	next[j] = '\0';
	free(buffer);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*str[10240];
	char		*ligne;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		if (str[fd])
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = read_lines(fd, str[fd]);
	if (str[fd] == NULL)
		return (NULL);
	ligne = current_line(str[fd]);
	str[fd] = next_line(str[fd]);
	return (ligne);
}
