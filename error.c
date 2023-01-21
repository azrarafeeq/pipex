/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:03:02 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/17 19:47:22 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initial_arg_check(char **argv, int argc)
{
	char	**a;

	a = ft_split(argv[1], ' ');
	if (argc < 5 && ft_strcmp("here_doc", argv[1]) != 0)
	{
		write(2, "Arguments are less than 5\n", 27);
		close_fds(0, 1, 2, -1);
		free_char_array(a);
		exit(0);
	}
	else if (ft_strcmp("here_doc", a[0]) == 0 && argc < 6 && a[1] == NULL)
	{
		write(2, "Not enough arguments for here_doc \n", 36);
		close_fds(0, 1, 2, -1);
		free_char_array(a);
		exit(0);
	}
	free_char_array(a);
}

void	path_error(char *command, char **envp, t_path *path, t_pfd *p_fd)
{
	write(2, command, ft_strlen(command));
	if (get_path(envp) == NULL)
		write(2, ": no such file or directory", 28);
	else
		write(2, ": command not found", 20);
	write(2, "\n", 1);
	close_fds(0, 1, 2, -1);
	free_pfd(p_fd);
	free_path(path);
	exit(0);
}

void	empty_arg_error(char *argv, t_path *path, t_pfd *p_fd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(argv);
	while (argv[i] == ' ' && argv[i])
		i++;
	if (!argv[0] || i == len)
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": command not found\n", 21);
		close_fds(0, 1, 2, -1);
		free_pfd(p_fd);
		free_path(path);
		exit(127);
	}
}

int	input_file_error(int fd, char *filename)
{
	char	**array;

	array = ft_split(filename, ' ');
	if (fd == -1 && !(ft_strcmp(array[0], "here_doc") == 0 && array[1] == NULL))
	{
		write(2, filename, ft_strlen(filename));
		write(2, ": no such file or directory", 28);
		write(2, "\n", 1);
		free_char_array(array);
		return (-1);
	}
	else if (ft_strcmp(array[0], "here_doc") == 0 && array[1] == NULL)
		free_char_array(array);
	else
	{
		close(fd);
		free_char_array(array);
	}
	return (0);
}

int	output_file_error(int fd, char *filename, t_pfd *p)
{
	if (fd == -1)
	{
		write(2, filename, ft_strlen(filename));
		write(2, ": no such file or directory", 28);
		write(2, "\n", 1);
		close(p->fd[p->s - 1][0]);
		close(p->fd[p->s - 1][1]);
		close_fds(0, 1, 2, -1);
		return (-1);
	}
	return (0);
}
