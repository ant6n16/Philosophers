/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:12:17 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/17 15:12:04 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(int argc, char **argv)
{
	int		i;
	char	aux;
	int		cont;

	if (argc != 5 && argc != 6)
		return (printf("You must pass 4 or 5 arguments\n"), -1);
	cont = argc - 1;
	while (cont)
	{
		i = -1;
		while (argv[cont][++i])
		{
			aux = argv[cont][i];
			if (aux < '0' || aux > '9')
				return (printf("Only positive integers allowed\n"), -1);
		}
		cont--;
	}
	return (0);
}

int	create_table(int argc, char **argv, t_table *table)
{
	if (argc == 6)
	{
		table->n_must_eat = ft_atoi_philo(argv[5]);
		table->early_finish = 1;
	}
	else
		table->early_finish = 0;
	table->num_p = ft_atoi_philo(argv[1]);
	if (table->num_p == 0)
		return (printf("Error: 0 philosophers is not valid\n"), -1);
	table->msg_die = ft_atoi_philo(argv[2]);
	table->msg_eat = ft_atoi_philo(argv[3]);
	table->msg_sleep = ft_atoi_philo(argv[4]);
	table->advance = 1;
	return (0);
}

int	create_philo(t_table *table, t_ph *philos)
{
	int	index;

	index = 0;
	while (index < table->num_p)
	{
		if (pthread_mutex_init(&philos[index].fork_r, NULL))
			return (printf("Error when creating mutex\n"), -1);
		if (pthread_mutex_init(&philos[index].eat_mtx, NULL))
			return (printf("Error when creating mutex\n"), -1);
		if (index != 0)
			philos[index].fork_l = &philos[index - 1].fork_r;
		philos[index].philo_dni = index + 1;
		philos[index].num_eats = 0;
		philos[index].when_last_eat = ft_get_time();
		philos[index].table = table;
		index++;
	}
	philos[0].fork_l = &philos[index - 1].fork_r;
	if (pthread_mutex_init(&philos->table->print_mtx, NULL))
		return (printf("Error when creating mutex\n"), -1);
	if (pthread_mutex_init(&philos->table->advance_mtx, NULL))
		return (printf("Error when creating mutex\n"), -1);
	table->now = ft_get_time();
	return (0);
}
