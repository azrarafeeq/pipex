/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:27:32 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/18 16:21:10 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

typedef struct s_pfd {
	int	**fd;
	int	s;
}				t_pfd;

typedef struct s_path {
	char	**cs;
	char	*path;
}				t_path;

t_pfd	*allocate_fd(int argc);

char	*get_path(char **envp);

int		paths_count(char *path);

char	**path_array(char *path);

char	*check_path(char **path_array, char *command);

void	process_1(char **argv, t_pfd *p_fd, char **envp, int a);

void	mid(char *argv, t_pfd *p, int i, char **envp);

void	process_2(char **argv, int argc, t_pfd *p, char **envp);

int		open_file_process_2(char **argv, int argc, t_pfd *p);

char	*ft_strjoin(char const *s1, char const *s2);

void	path_error(char *command, char **envp, t_path *path, t_pfd *p_fd);

int		pid_error(int pid);

int		input_file_error(int fd, char *filename);

int		output_file_error(int fd, char *filename, t_pfd *p);

void	empty_arg_error(char *argv, t_path *path, t_pfd *p_fd);

void	initial_arg_check(char **argv, int argc);

void	free_char_array(char **array);

void	free_pfd(t_pfd *p_fd);

void	free_path(t_path *path);

void	close_fds(int fd1, int fd2, int fd3, int fd4);

void	bonus_here_doc(char **argv, int *argc);

#endif