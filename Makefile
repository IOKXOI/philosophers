# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 18:03:36 by sydauria          #+#    #+#              #
#    Updated: 2023/01/03 18:28:55 by sydauria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRCS =	srcs/args_traitement.c \
		srcs/atoi_ptr.c \
		srcs/init.c \
		srcs/main.c \
		srcs/manager.c \
		srcs/mutex.c \
		srcs/routine.c\
OBJS = ${SRCS:.c=.o}
INCLUDES = includes

all: ${NAME}

%.o:%.c ./includes/*.h
	@$(CC) ${CFLAGS} -I$(INCLUDES) -c $< -o $@

${NAME} : ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o philo
	@printf "%s\e[0;32m philosopher : Compiling object file into executable\n\e[0m" "-"

clean:
	rm -rf ${OBJS}
	@printf "%s\e[0;31m philosopher : Delete all object files\n\e[0m" "-"

fclean:
	clean
	@printf "%s\e[0;31m philosopher : Delete all object files\n\e[0m" "-"
	rm -rf ${NAME}
	@printf "%s\e[0;31m philosopher : Delete executable\n\e[0m" "-"

re: fclean ${NAME}

.PHONY: all clean fclean re
NAME=philo
CC=cc
CFLAGS=-Wall -Werror -Wextra -MMD -g3
SRCDIR= srcs/
OBJSDIR=./objs/
BUILD = build
INCLUDES =./includes

SRCS=	

################################################################################
#                                     OBJECTS                                  #
################################################################################

OBJS := $(SRCS:%.c=%.o)

################################################################################
#                                     RULES                                    #
################################################################################

all: $(NAME)

-include:$(DEPS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -I $(INCLUDES) -o $@

%.o: %.c ./includes/*.h
	@mkdir -p '$(@D)'
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean
	make

.PHONY: all clean fclean re
