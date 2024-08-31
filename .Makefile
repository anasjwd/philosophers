# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajawad <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 10:07:38 by ajawad            #+#    #+#              #
#    Updated: 2024/08/31 02:22:55 by ajawad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

HEADER	=	./includes/philo.h

CFILES	=	main.c printing.c utils.c parsing.c initialize.c \
			start_simulation.c routine.c monitor.c
SRC		=	$(addprefix src/,$(CFILES))
OBJS	=	${SRC:.c=.o}

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=thread
PFLAG	=	-O3 -pthread
RM		=	rm -f

all: ${NAME}

%.o:%.c
	${CC} ${CFLAGS} -Iincludes -c $< -o $@

${NAME}	:	${OBJS} ${HEADER}
	${CC} ${CFLAGS} ${OBJS} ${PFLAG} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean
.SECONDARY: ${OBJS}
