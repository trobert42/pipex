# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobert <trobert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:43:19 by trobert           #+#    #+#              #
#    Updated: 2022/05/02 15:10:28 by trobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	pipex.c\
		pipex_utils.c\
		parsing.c\
		free_quit_functions.c\

BSRC =	pipex_bonus.c\
		init_var_bonus.c\
		fd_functions_bonus.c\
		cmds_functions_bonus.c\
		pipex_utils_bonus.c\
		here_doc_bonus.c\
		free_quit_functions_bonus.c\

SRCS = ${addprefix srcs/, ${SRC}}

BSRCS = ${addprefix srcs_bonus/, ${BSRC}}

OBJS = ${SRCS:.c=.o}

BOBJS = ${BSRCS:.c=.o}

INC = -I./includes -I./libft/includes

NAME = pipex

BNAME = pipex_bonus

LIBFT = libft/superlibft.a

CC = cc -g

RM = rm -f

CFLAGS = -Wall -Wextra

MAKELIB = make -C libft/

CLEANLIB = make fclean -C libft/

all: libcompil ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${INC} ${LIBFT} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

bonus: libcompil ${BNAME}

${BNAME}: ${BOBJS}
	${CC} ${CFLAGS} ${BOBJS} ${INC} ${LIBFT} -o ${BNAME}

libcompil :
	${MAKELIB}

clean:
	${RM} ${OBJS} ${BOBJS}

fclean: clean libclean
	${RM} ${NAME} ${BNAME}

libclean:
	${CLEANLIB}

re: fclean all

.PHONY: clean fclean bonus all re
