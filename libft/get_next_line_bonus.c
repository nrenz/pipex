/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:06:01 by nrenz             #+#    #+#             */
/*   Updated: 2022/10/12 16:21:14 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	output = (char *)malloc(BUFFER_SIZE);
	if (!output)
		return (NULL);
	output[0] = '\0';
	return (ft_gnl_check(buffer[fd], output, fd));
}

char	*ft_gnl_check(char *buffer, char *output, int fd)
{
	ssize_t	read_done;

	while (1)
	{
		if (buffer[0])
		{
			if (ft_strchr_gnl(buffer, '\n'))
			{
				return (ft_found_new_line(buffer, output));
			}
			output = ft_realloc(output, buffer, 1, 0);
		}
		read_done = read(fd, buffer, BUFFER_SIZE);
		if (read_done == -1 || (read_done == 0 && output[0] == '\0'))
		{
			free(output);
			return (NULL);
		}
		buffer[read_done] = '\0';
		if (read_done == 0)
		{
			return (output);
		}
	}
}

char	*ft_found_new_line(char *buffer, char *output)
{
	int		cut_size;
	char	*tmp;

	tmp = (char *)malloc(BUFFER_SIZE);
	cut_size = (ft_strchr_gnl(buffer, '\n') - buffer) + 1;
	if (!tmp)
		return (NULL);
	ft_copy(tmp, buffer, cut_size + 1);
	output = ft_realloc(output, tmp, 1, 1);
	ft_copy(buffer, &buffer[cut_size], 0);
	return (output);
}

char	*ft_realloc(char *s1, char *s2, int free_s1, int free_s2)
{
	int		strlen_s1;
	int		strlen_s2;
	char	*new_output;
	int		count;

	strlen_s1 = ft_strlen_gnl(s1);
	strlen_s2 = ft_strlen_gnl(s2);
	new_output = (char *)malloc(strlen_s1 + strlen_s2 + 1);
	if (!new_output)
		return (NULL);
	count = ft_copy(new_output, s1, 0);
	ft_copy(&new_output[count], s2, 0);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (new_output);
}
