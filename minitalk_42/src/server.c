#include "../headers/minitalk.h"

static void	ft_putstr_fd(char *s, int fd)
{
	char	*first;

	first = s;
	if (fd == -1)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	s = first;
}

static void	handler(int signal)
{
    //contar la cantidad de bits y el caracter que acumula
	static int				bits_counter = 0;
	static unsigned char	c = '\0';

    /*
    c se desplaza a la izquierda (c <<= 1), 
    */
	c <<= 1;
	if (signal == SIGUSR1)
        //y si la señal recibida es SIGUSR1, el bit menos significativo de c 
        //se establece en 1 (c |= 1), sino es 0.
		c |= 1;
	bits_counter++;
    // Si se han acumulado 8 bits (un byte)
	if (bits_counter == 8)
	{
        // Imprime el byte acumulado (el caracter) y se setea lo demas a 0 para el prox caracter
		ft_putchar_fd(c, 1);
		bits_counter = 0;
		c = '\0';
	}
}

static void	print_server_pid()
{
    pid_t				server_pid;

    //obtenemos el pid (pid_t) y luego imprimimos el numero
    //de PID si el mismo no falla, el cast para entero para el ptnbr
	server_pid = getpid();
    if (!server_pid)
		ft_putendl_fd("No Server PID", 2);
	else
	{
        ft_putstr_fd("Server PID :", 1);
	    ft_putnbr_fd((int)server_pid, 1);
	    write(1, "\n", 1);
    }
}

static void	init_sigaction()
{
    // Estructura para configurar el manejo de señales
	struct sigaction	sa;

    //Inicializa el conjunto de señales (sa.sa_mask) asociado 
    //a la estructura sa como un conjunto vacío. Esto significa 
    //que inicialmente no se bloquearán señales al activar.
    sigemptyset(&sa.sa_mask);

    //Agrega las señales SIGUSR1 y SIGUSR2 al conjunto de señales (sa.sa_mask). 
    //Esto indica que, cuando el manejador de señales (handler) se está ejecutando, 
    //estas señales estarán bloqueadas para prevenir interrupciones durante 
    //la ejecución del manejador.
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);

    //Asigna la función handler como el manejador de señales para las señales especificadas.
	sa.sa_handler = handler;

    //Establece la bandera SA_RESTART. Esta bandera indica que si una llamada 
    //al sistema es interrumpida por la ejecución  del manejador de señales, 
    //la llamada al sistema se reiniciará automáticamente después de que 
    //el manejador haya terminado. 
    sa.sa_flags = SA_RESTART;

	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		exit(EXIT_FAILURE);
}

int	main(void)
{
	print_server_pid();
	init_sigaction();
    while (1)
		pause();
    return (0);
}

/*
configura un manejador de señales (handler) para 
las señales SIGUSR1 y SIGUSR2. Cuando se recibe 
una de estas señales, se ejecutará la función 
handler, y durante la ejecución de esta función, 
se bloquearán las señales SIGUSR1 y SIGUSR2 para 
evitar interrupciones adicionales durante el manejo de 
la señal. Además, se utiliza SA_RESTART para reiniciar 
llamadas de sistema interrumpidas automáticamente.
*/
