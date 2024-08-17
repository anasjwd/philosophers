# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajawad <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 10:07:38 by ajawad            #+#    #+#              #
#    Updated: 2024/08/16 03:07:11 by ajawad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

HEADER	=	./includes/minishell.h

CFILES	=	philo.c printing.c parsing.c start_simulation.c routine.c \
			actions.c utils.c monitor.c
SRC		=	$(addprefix src/,$(CFILES))
OBJS	=	${SRC:.c=.o}

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=thread
PFLAG	=	-pthread
RM		=	rm -f

all: ${NAME}

%.o:%.c
	${CC} ${CFLAGS} -Iincludes -c $< -o $@

${NAME}	:	${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${PFLAG} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
.SECONDARY: ${OBJS}
