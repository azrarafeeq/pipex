/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:27:29 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/17 16:38:54 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pfd	*p_fd;
	int		ints[3];

	ints[0] = -1;
	ints[1] = argc - 2;
	ints[2] = argc;
	initial_arg_check(argv, argc);
	bonus_here_doc(argv, &argc);
	p_fd = allocate_fd(argc);
	pipe(p_fd->fd[0]);
	process_1(argv, p_fd, envp, 2);
	while (argc >= 6 && ++ints[0] != argc - 5)
	{
		pipe(p_fd->fd[ints[0] + 1]);
		if (ft_strncmp(argv[1], "temp", 4) == 0)
			mid(argv[ints[0] + 4], p_fd, ints[0], envp);
		else
			mid(argv[ints[0] + 3], p_fd, ints[0], envp);
	}
	process_2(argv, ints[2], p_fd, envp);
	free_pfd(p_fd);
	while (--ints[1])
		waitpid(-1, 0, 0);
	unlink("temp");
	return (0);
}

void	process_1(char **argv, t_pfd *p_fd, char **en, int a)
{
	int		num[2];
	t_path	*pt;

	if (ft_strncmp(argv[1], "temp", 4) == 0)
		a = 3;
	num[0] = open(argv[1], O_RDONLY, 0777);
	if (input_file_error(open(argv[1], O_RDONLY), argv[1]) == -1)
		return ;
	pt = malloc(sizeof(t_path));
	pt->cs = ft_split(argv[a], ' ');
	pt->path = check_path(path_array(get_path(en)), ft_strjoin("/", pt->cs[0]));
	num[1] = fork();
	if (pid_error(num[1]) == 0)
	{
		dup2(num[0], STDIN_FILENO);
		dup2(p_fd->fd[0][1], STDOUT_FILENO);
		close_fds(p_fd->fd[0][0], p_fd->fd[0][1], num[0], -1);
		empty_arg_error(argv[a], pt, p_fd);
		if ((ft_strrchr(pt->cs[0], '/') && execve(pt->cs[0], pt->cs, en) == -1)
			|| (pt->path == NULL || execve(pt->path, pt->cs, en) == -1))
			path_error(argv[a], en, pt, p_fd);
	}
	free_path(pt);
	close(num[0]);
}

void	process_2(char **argv, int argc, t_pfd *p, char **en)
{
	int		num[2];
	t_path	*pt;

	num[0] = open_file_process_2(argv, argc, p);
	if (num[0] == -1)
		return ;
	pt = malloc(sizeof(t_path));
	pt->cs = ft_split(argv[argc - 2], ' ');
	pt->path = check_path(path_array(get_path(en)), ft_strjoin("/", pt->cs[0]));
	num[1] = fork();
	if (pid_error(num[1]) == 0)
	{
		dup2(p->fd[p->s - 1][0], STDIN_FILENO);
		dup2(num[0], STDOUT_FILENO);
		close_fds(p->fd[p->s - 1][0], p->fd[p->s - 1][1], num[0], -1);
		empty_arg_error(argv[argc - 2], pt, p);
		if ((ft_strrchr(pt->cs[0], '/') && execve(pt->cs[0], pt->cs, en) == -1)
			|| (pt->path == NULL || execve(pt->path, pt->cs, en) == -1))
			path_error(argv[argc - 2], en, pt, p);
	}
	free_path(pt);
	close_fds(0, 1, 2, -1);
	close_fds(p->fd[p->s - 1][0], p->fd[p->s - 1][1], num[0], -1);
}

int	open_file_process_2(char **argv, int argc, t_pfd *p)
{
	int	fd;

	if (ft_strncmp(argv[1], "temp", 4) == 0)
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_file_error(fd, argv[argc - 1], p) == -1)
		return (-1);
	return (fd);
}
