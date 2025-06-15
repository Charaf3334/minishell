# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 13:32:20 by ctoujana          #+#    #+#              #
#    Updated: 2025/06/15 11:44:26 by ctoujana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	libft/ft_strlen.c libft/ft_memcpy.c libft/ft_strdup.c libft/ft_itoa.c libft/ft_split_normal.c libft/ft_split_not_normal.c \
	libft/ft_split.c libft/ft_split_leaks.c libft/ft_split_quoted.c libft/ft_split_libft.c libft/ft_split_quoted_utils.c libft/ft_strjoin.c libft/ft_strjoin3.c libft/ft_substr.c  libft/ft_split_utils.c  \
	libft/ft_strchr.c libft/ft_strcmp.c libft/ft_putstr_fd.c libft/ft_strtrim.c \
	libft/ft_ltadd_back.c libft/ft_atol.c\
	main.c \
	parsing/garbage_col.c parsing/handler.c parsing/utils7.c \
	parsing/handler_utils.c parsing/handler_utils2.c parsing/handler_utils3.c\
	parsing/utils3.c parsing/utils4.c parsing/utils5.c parsing/utils6.c\
	parsing/syntax_error.c parsing/syntax_error2.c parsing/syntax_error3.c parsing/utils1.c parsing/utils2.c  \
	parsing/expand_utils.c parsing/expand_utils2.c parsing/expand_utils3.c parsing/expand_utils6.c \
	parsing/expand_utils4.c parsing/expand_utils5.c parsing/expand_in_out_utils.c \
	execution/builtins.c \
	execution/builtins_utils.c execution/check_access.c execution/env.c execution/exec_cmd.c execution/execute_nodes.c \
	execution/exec_utils1.c execution/exec_utils2.c execution/exec_utils3.c execution/exec_utils4.c execution/handle_exit.c \
	execution/open_here_doc_utils.c execution/open_here_doc.c execution/extract_strs.c execution/export.c \
	execution/export_utils1.c execution/export_utils2.c execution/cd_utils2.c execution/here_doc_utils.c \
	execution/extract_ll.c execution/cd.c execution/cd_utils.c execution/execute.c \
	parsing/expand.c parsing/expand_in_out.c parsing/utils8.c
OBJS = $(SRCS:.c=.o)
NAME = minishell


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
