NAME_SERVER = server
NAME_CLIENT = client

HEADERS = headers/minitalk.h
SRCS = src/server.c src/client.c src/utils.c
OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

all: ${NAME_SERVER} ${NAME_CLIENT}

${NAME_SERVER}: ${OBJS} Makefile ${HEADERS}
	${CC} ${CFLAGS} src/server.o src/utils.o -o ${NAME_SERVER}

${NAME_CLIENT}: ${OBJS} Makefile ${HEADERS}
	${CC} ${CFLAGS} src/client.o src/utils.o -o ${NAME_CLIENT}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME_SERVER}
	rm -f ${NAME_CLIENT}

re: fclean all

.PHONY: all clean fclean re
