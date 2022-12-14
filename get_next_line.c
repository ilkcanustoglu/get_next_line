/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iustoglu <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:27:42 by iustoglu          #+#    #+#             */
/*   Updated: 2022/06/15 15:27:42 by iustoglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*move_line(char *s)
{
	char	*dest;

	dest = ft_strchr(s, '\n');
	if (!dest)
	{
		free(s);
		return (NULL);
	}
	if (*(dest + 1))
		dest = ft_strdup(dest + 1);
	else
		dest = NULL;
	free(s);
	return (dest);
}

char	*read_word(int fd, char *buffer, char **s)
{
	int		size;
	char	*dest;

	size = read(fd, buffer, BUFFER_SIZE);
	if (size == -1)
		return (NULL);
	buffer[size] = 0;
	while (size > 0)
	{
		if (!*s)
			*s = ft_strdup(buffer);
		else
			*s = ft_strjoin(*s, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		size = read(fd, buffer, BUFFER_SIZE);
		buffer[size] = 0;
	}
	free(buffer);
	dest = ft_substr(*s, 0, ft_strchr(*s, '\n') - *s + 1);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*dest;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, buffer, 0) == -1)
	{
		free(buffer);
		return (0);
	}
	dest = read_word(fd, buffer, &s);
	s = move_line(s);
	return (dest);
}
/*
int main()
{
    int fd1 = open("test.txt", O_RDONLY);

    char *nl;
    char *yy;
    int i;
while(i<10)
{
  	 nl = get_next_line(fd1);
        printf("%s", nl);      
    i++;
}
}
*/