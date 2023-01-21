/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:17:57 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/17 16:16:51 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mid(char *argv, t_pfd *p, int i, char **en)
{
	int		pid;
	t_path	*pt;

	pt = malloc(sizeof(t_path));
	pt->cs = ft_split(argv, ' ');
	pt->path = check_path(path_array(get_path(en)), ft_strjoin("/", pt->cs[0]));
	pid = fork();
	if (pid_error(pid) == 0)
	{
		dup2(p->fd[i][0], STDIN_FILENO);
		dup2(p->fd[i + 1][1], STDOUT_FILENO);
		close_fds(p->fd[i][0], p->fd[i][1], p->fd[i + 1][0], p->fd[i + 1][1]);
		empty_arg_error(argv, pt, p);
		if ((ft_strrchr(pt->cs[0], '/') && execve(pt->cs[0], pt->cs, en) == -1)
			|| pt->path == NULL || execve(pt->path, pt->cs, en) == -1)
			path_error(argv, en, pt, p);
	}
	free_path(pt);
	close_fds(p->fd[i][0], p->fd[i][1], -1, -1);
}

void	bonus_here_doc(char **argv, int *argc)
{
	int		fd;
	char	*line;
	char	**array;

	array = ft_split(argv[1], ' ');
	if ((ft_strcmp("here_doc", array[0]) == 0) && array[1] == NULL)
	{
		line = get_next_line(0);
		fd = open("temp", O_RDWR | O_CREAT, 0777);
		while (line)
		{
			if (ft_strcmp(argv[2], line) == 0)
				break ;
			ft_putstr_fd(line, fd);
			free(line);
			line = get_next_line(0);
		}
		free(line);
		*argc = *argc - 1;
		argv[1] = "temp";
		close(fd);
	}
	free_char_array(array);
}

t_pfd	*allocate_fd(int argc)
{
	t_pfd	*p_fd;
	int		i;

	i = 0;
	p_fd = malloc(sizeof(t_pfd));
	if ((argc - 4) > 256)
	{
		write(2, "Error in allocating memory\n", 28);
		free(p_fd);
		exit(0);
	}
	p_fd->fd = (int **)malloc (sizeof(int *) * (argc - 4));
	while (i < (argc - 4))
	{
		p_fd->fd[i] = (int *)malloc (sizeof(int) * 2);
		i++;
	}
	p_fd->s = argc - 4;
	return (p_fd);
}
