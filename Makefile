NAME_SERVER = server
NAME_CLIENT = client

HEADERS 	= 	headers/minitalk.h 

SRCS 		= src/server.c src/client.c src/utils.c

OBJS 		= ${SRCS:.c=.o}

CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra -fsanitize=address -g

%o:%c

${NAME_SERVER} : src/server.o src/utils.o Makefile headers/minitalk.h
				 ${CC} ${CFLAGS} src/server.o src/utils.o -o ${NAME_SERVER}

${NAME_CLIENT} : src/client.o src/utils.o Makefile headers/minitalk.h
				 ${CC} ${CFLAGS} src/client.o src/utils.o -o ${NAME_CLIENT}
				 

all: 		${NAME_SERVER} ${NAME_CLIENT}

clean:
			rm -f ${OBJS}

fclean: 	clean
			rm -f ${NAME_SERVER}
			rm -f ${NAME_CLIENT}

re: 		fclean all

.PHONY: 	all clean fclean re
