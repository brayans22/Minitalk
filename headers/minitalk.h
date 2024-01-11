#ifndef MINITALK_H
# define MINITALK_H

/* INCLUDES */

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include "minitalk.h"

/* CONSTANTS */
# define ERROR -1

/* FUNCTIONS */
int     ft_strlen(const char *s1);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);

#endif