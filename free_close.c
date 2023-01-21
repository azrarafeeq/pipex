/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:55 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/18 15:18:15 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_pfd(t_pfd *p_fd)
{
	int	i;

	i = 0;
	while (i < p_fd->s)
	{
		free(p_fd->fd[i]);
		i++;
	}
	free(p_fd->fd);
	free(p_fd);
}

void	free_path(t_path *path)
{
	free_char_array(path->cs);
	free(path->path);
	free(path);
}

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (fd4 != -1)
		close(fd4);
	return ;
}

int	pid_error(int pid)
{
	if (pid == -1)
	{
		perror("Error ");
		exit(1);
	}
	return (pid);
}
