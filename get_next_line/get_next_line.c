/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 13:53:47 by rbagin        #+#    #+#                 */
/*   Updated: 2024/11/21 17:08:09 by rbagin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	size_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	if (!left_c)
		left_c = ft_strdup("");
	temp = ft_strjoin(left_c, buffer);
	free(left_c);
	return (temp);
}

char	*extract_line(char *line_buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	line = ft_substr(line_buffer, 0, i +1);
	return (line);
}

char	*handle_left_c(char *line_buffer)
{
	char	*left_c;
	size_t	i;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	left_c = ft_substr(line_buffer, i, ft_strlen(line_buffer) - i);
	free(line_buffer);
	return (left_c);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*left_c = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	left_c = fill_line_buffer(fd, left_c, buffer);
	free(buffer);
	if (!left_c)
		return (NULL);
	line = extract_line(left_c);
	left_c = handle_left_c(left_c);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("testing.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file");
	}
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
		line = get_next_line(fd);
	printf("%s", line);
	free(line);
		line = get_next_line(fd);
	printf("%s", line);
	free(line);
		line = get_next_line(fd);
	printf("%s", line);
	free(line);
		line = get_next_line(fd);
	printf("%s", line);
	free(line);
	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// }
	if (close(fd) < 0)
	{
		printf("Error closing file");
		return (1);
	}
	return (0);
}
