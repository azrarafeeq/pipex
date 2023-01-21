# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 17:27:20 by arafeeq           #+#    #+#              #
#    Updated: 2023/01/18 16:21:03 by arafeeq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex path bonus error free_close

GNLSRCS = ./get_next_line/get_next_line.c\
			./get_next_line/get_next_line_utils.c

OBJDIR = objects

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = -Llibft -lft

$(OBJDIR)/%.o : %.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		make all -C libft
		$(CC) $(CFLAGS) $(OBJS) $(GNLSRCS) $(LIBFT) -o $(NAME)

clean :
		make clean -C libft
		rm -rf $(OBJDIR)

fclean : clean
		make fclean -C libft
		rm -f $(NAME)

re : fclean all