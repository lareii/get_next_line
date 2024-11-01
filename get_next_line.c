/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:17:53 by ebabaogl          #+#    #+#             */
/*   Updated: 2024/11/01 16:52:20 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*line;

	char		*buf;
	ssize_t		r_bytes;

	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(left_str), NULL);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes <= 0)
			break;
		buf[r_bytes] = '\0';
		tmp = ft_strjoin(left_str, buf);
		free(left_str);
		left_str = tmp;
		
		char *newline = ft_strchr(left_str, '\n');
		if (newline)
		{
			line = ft_substr(left_str, 0, newline - left_str + 1);
			char *new_left_str = ft_substr(left_str, newline - left_str + 1, strlen(newline + 1));
			free(left_str);
			left_str = new_left_str;
			return (line);
		}
	}
	return (NULL);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
}
