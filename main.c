/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:08:10 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/19 19:17:53 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_ph	*philos;
	int		i;

	if (check_arg(argc, argv) || create_table(argc, argv, &table))
		return (-1);
	philos = (t_ph *) malloc(sizeof(t_ph) * table.num_p);
	if (create_philo(&table, philos))
		return (-1);
	table.now = ft_get_time();
	if (table.num_p == 1)
	{
		if (pthread_create(&philos[0].thread, NULL, one_philo, &philos[0]))
			return (printf("Error creating threads\n"), -1);
	}
	else
	{
		i = -1;
		while (++i < table.num_p)
			if (pthread_create(&philos[i].thread, NULL, philo_thread, &philos[i]))
				return (printf("Error creating threads\n"), -1);
		if (pthread_create(&table.die_no_eat, NULL, check_thread, philos))
			return (printf("Error creating threads\n"), -1);
	}
	i = -1;
	while (++i < philos->table->num_p)
		pthread_join(philos[i].thread, NULL);
	pthread_join(philos->table->die_no_eat, NULL);
	i = -1;
	while (++i < philos->table->num_p)
	{
		pthread_mutex_destroy(&philos[i].fork_r);
		pthread_mutex_destroy(&philos[i].eat_mtx);
	}
	pthread_mutex_destroy(&philos->table->print_mtx);
	pthread_mutex_destroy(&philos->table->advance_mtx);
	return (0);
}

// CERRAR TODOS LOS MUTEX, LIBERAR MALLOCS, CHEQUEAR LEAKS, DATARACES...
