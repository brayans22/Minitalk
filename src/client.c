#include "../headers/minitalk.h"

static void send_signal_bits(char character, pid_t pid_server)
{
    int bits;

    bits = 7; 
    while (bits >= 0)
    {
        if ((character >> bits & 1) == 1)
            kill(pid_server, SIGUSR1);
        else
            kill(pid_server, SIGUSR2);
        --bits;
        usleep(80);
    }
}

static int is_valid_arguments(char *pid, char *msg)
{
    int len_pid;
    int len_msg;

    len_pid = ft_strlen(pid);
    len_msg = ft_strlen(msg);
    if (len_pid == 0 || len_pid > 5)
        return (-2);
    else if (len_msg == 0)
        return (-1);
    else
    {
        while (*pid)
        {
            if (!(*pid >= '0' && *pid <= '9'))
                return (-2);
            pid++;
        }
    }
    return (1);
}

int main(char **argv, int argc)
{
    int j;
    int status;
    char c;

    j = -1;
    if (argc == 3)
    {
        status = is_valid_arguments(argv[1], argv[2]);
        if (status == -1)
            ft_putendl_fd("Error\n You cannot sent a void msg", 1);
        else if (status == -2)
            ft_putendl_fd("Error\n Invalid PID!", 1);
        else
        {
            while (argv[2][++j])
            send_signal_bits(argv[2][j], ft_atoi(argv[1]));
        }         
    }
    else
    {
        ft_putendl_fd("Error\n you have to sent 3 arguments with this format", 1);
        ft_putendl_fd("./client (PID) (Message)", 1);
    }
    return (0);
}
