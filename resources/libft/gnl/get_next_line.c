/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:23:47 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:16:45 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/get_next_line.h"

char	*ft_extract(char *stash)
{
	int		i;
	int		j;
	char	*nouvelle_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	nouvelle_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	i++;
	j = 0;
	while (stash[i])
	{
		nouvelle_stash[j] = stash[i];
		j++;
		i++;
	}
	free (stash);
	nouvelle_stash[j] = '\0';
	return (nouvelle_stash);
}

char	*ft_ligne(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*free_all(char	*str, char	*stash)
{
	free (str);
	free (stash);
	return (NULL);
}

char	*ft_read(int fd, char *stash)
{
	char	*tmp;
	char	*str;
	int		lu;

	if (!stash)
		stash = ft_strdup("");
	lu = 1;
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (!ft_strchr(stash, '\n') && lu != 0)
	{
		lu = read(fd, str, BUFFER_SIZE);
		if (lu == -1)
			return (free_all(str, stash));
		str[lu] = '\0';
		tmp = ft_strjoin(stash, str);
		free(stash);
		stash = tmp;
	}
	free(str);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_ligne(stash);
	stash = ft_extract(stash);
	if (line[0] == '\0')
	{
		free (stash);
		free (line);
		return (NULL);
	}
	return (line);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	fd;
// 	char *line;
// 	fd = open("get_next_line.c", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break;
// 		printf("%s", line);
// 		free (line);
// 	}
// }