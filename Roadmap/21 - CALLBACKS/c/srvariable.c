/*
 * EJERCICIO:
 * Explora el concepto de callback en tu lenguaje creando un ejemplo
 * simple (a tu elección) que muestre su funcionamiento.
 *
 * DIFICULTAD EXTRA (opcional):
 * Crea un simulador de pedidos de un restaurante utilizando callbacks.
 * Estará formado por una función que procesa pedidos.
 * Debe aceptar el nombre del plato, una callback de confirmación, una
 * de listo y otra de entrega.
 * - Debe imprimir un confirmación cuando empiece el procesamiento.
 * - Debe simular un tiempo aleatorio entre 1 a 10 segundos entre
 *   procesos.
 * - Debe invocar a cada callback siguiendo un orden de procesado.
 * - Debe notificar que el plato está listo o ha sido entregado.
 */

/* @------------------------------------------------------------------------@ */
/* |                       Inclusión de bibliotecas                         | */
/* @------------------------------------------------------------------------@ */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/* @------------------------------------------------------------------------@ */
/* |                           Creación de tipos                            | */
/* @------------------------------------------------------------------------@ */

typedef void (*Callback)(void *);
typedef struct
{
	char	*name;
	int		time_to_process;
	bool	is_ready;
} Order;

/* @------------------------------------------------------------------------@ */
/* |                       Declaración de funciones                         | */
/* @------------------------------------------------------------------------@ */

void	send_data(void *data);
void	receive_data(void *data);
void	call_function(Callback cb, void *data);

void	receive_order(char *name, Callback confirm, Callback ready, Callback send);
void	confirm_order(void *data);
void	process_order(void *data);
void	ready_order(void *data);
void	send_order(void *data);

/* @------------------------------------------------------------------------@ */
/* |                           Función principal                            | */
/* @------------------------------------------------------------------------@ */

int	main(void)
{
	int	n;

	srand(time(NULL));
	call_function(&send_data, &n);
	call_function(&receive_data, &n);
	receive_order("Albóndigas", &confirm_order, &ready_order, &send_order);
	receive_order("Salmón", &confirm_order, &ready_order, &send_order);
	receive_order("Lentejas", &confirm_order, &ready_order, &send_order);
	receive_order("Tarta de chocolate", &confirm_order, &ready_order, &send_order);
	return (0);
}

/* @------------------------------------------------------------------------@ */
/* |                        Definición de funciones                         | */
/* @------------------------------------------------------------------------@ */

void	send_data(void *data)
{
	int	*number;

	if (!data)
	{
		fprintf(stderr, "Invalid data\n");
		return ;
	}
	number = data;
	printf("Sending data: %d\n", *number);
}

void	receive_data(void *data)
{
	int	*number;

	if (!data)
	{
		fprintf(stderr, "Invalid data\n");
		return ;
	}
	number = data;
	printf("Received the data: %d\n", *number);
}

void	call_function(Callback cb, void *data)
{
	cb(data);
}


/* @------------------------------------------------------------------------@ */
/* |                           Dificultad extra                             | */
/* @------------------------------------------------------------------------@ */

void	receive_order(char *name, Callback confirm, Callback ready, Callback send)
{
	Order	order;

	if (!name)
	{
		fprintf(stderr, "Invalid name\n");
		return ;
	}
	order.name = name;
	order.time_to_process = (rand()  + (int)strlen(name)) % 10 + 1;
	confirm(&order);
	ready(&order);
	if (order.is_ready)
		send(&order);
}

void	confirm_order(void *data)
{
	Order	*order;

	order = data;
	printf("Order %s received!\n", order->name);
	process_order(data);
}

void	process_order(void *data)
{
	Order	*order;

	order = data;
	printf("Start processing... It will take %d seconds...\n", order->time_to_process);
	sleep(order->time_to_process);
}

void	ready_order(void *data)
{
	Order	*order;

	order = data;
	printf("%s is ready!\n", order->name);
	order->is_ready = true;
}

void	send_order(void *data)
{
	Order	*order;

	order = data;
	printf("%s sent!\n", order->name);
}
