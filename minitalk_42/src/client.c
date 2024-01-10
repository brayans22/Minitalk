#include "../headers/minitalk.h"

void send_signal_bits(char character, pid_t pid_server)
{
    int bits;

    bits = 7;
    // ojo con character d
    // deberia ser un mensaje, dentro del while y es una palabra no una letra
    // PID ES UN ENTERO 
    //  PRINT BITS
    while (bits >= 0)
    {
        if ((character >> bits & 1) == 1)
            kill(pid_server, SIGUSR1);
        else
            kill(pid_server, SIGUSR1);
        --bits;
        usleep(80);
    }
    
}

int main(char **argv, int argc)
{
    int j;

    j = -1;
    if (argc == 3)
    {
        while (argv[2][++j])
            send_signal_bits(argv[2][j], ft_atoi(argv[1]));
    }
    else
    {
        ft_putendl_fd("Error\n you have to sent 3 arguments with this format", 1);
        ft_putendl_fd("./client (PID) (Message)", 1);
    }
    return (0);
}