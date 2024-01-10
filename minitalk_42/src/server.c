#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Función que convierte una cadena de caracteres (1 byte) a su representación binaria
int** char_to_bin(char* str)
{
    int** ptr;
    int  byte_index;
    int  bit_index;
    int  i;

    byte_index = 0;
    // Se calcula la cantidad de bytes en la cadena (hasta el caracter nulo)
    while (str[++byte_index]);

    // Se reserva memoria para almacenar las representaciones binarias de cada byte, más un espacio adicional para el marcador de fin
    ptr = calloc(byte_index + 1, sizeof(int*));
    if (!ptr)
        return(NULL);

    byte_index = 0;
    // Para cada byte en la cadena
    while (str[byte_index])
    {
        // Se reserva memoria para almacenar los bits de cada byte
        ptr[byte_index] = calloc(sizeof(int), 8);
        if (!ptr[byte_index])
            return(NULL);
        bit_index = 7;
        i = 0;
        // Se recorren los bits del byte
        while (bit_index >= 0) 
        {
            // Se obtiene el valor del bit en la posición actual
            ptr[byte_index][i++] = (str[byte_index] >> bit_index) & 1;
            printf("%d -> %d\n", str[byte_index] >> bit_index, (str[byte_index] >> bit_index) & 1);
            bit_index--;
        }
        printf(" : ");
        byte_index++;
    }
    return (ptr);
}

// Función que convierte una representación binaria a su carácter equivalente
int bin_to_char(int** ptr)
{
    static char  c; // Variable estática para almacenar el carácter resultante
    int    byte_idx;
    int    bit_idx;
    int    val;

    byte_idx = 0;
    printf("Value per 8 bit -> ");
    // Para cada conjunto de bits en la representación binaria
    while (ptr[byte_idx])
    {
        bit_idx = 0;
        // Se recorren los bits
        while (bit_idx < 8)
        {
            // Se obtiene el valor del bit en la posición actual
            val = ptr[byte_idx][bit_idx];
            if (val == 1)
                c = (c << 1) | 1;
            else if (val == 0)
                c <<= 1;
            bit_idx++;
        }
        printf("%d : ", c);
        byte_idx++;
    }
    return (c);
}

// Función principal
int main(void) {
   char str[2] = "H"; // Cadena de caracteres que contiene un solo carácter ('H')
   int** ptr;

   // Se llama a la función para convertir el carácter a su representación binaria
   ptr = char_to_bin(str);

   // Se llama a la función para convertir la representación binaria de nuevo al carácter original
   bin_to_char(ptr);
   
   return (0);
}
