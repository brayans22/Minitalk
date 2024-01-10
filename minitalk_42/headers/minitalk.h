#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "minitalk.h"

/* Mandatory */
int     ft_strlen(const char *s1);
int		ft_atoi(const char *str);

/* Additional Functions */
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);

#endif