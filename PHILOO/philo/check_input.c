/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 00:14:28 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 19:27:41 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Retorna -1 cuando hay un error, 0 si todo OK*/
int	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		ft_exit_error("Invalid number of arguments: 4 or 5 expected\n");
		return (-1);
	}
	i = 0;
	while (--argc > 0)
	{
		i = -1;
		while (argv[argc][++i])
		{
			if (argv[argc][i] < '0' || argv[argc][i] > '9')
			{
				ft_exit_error("Only positive numbers allowed\n");
				return (-1);
			}
		}
	}
	return (0);
}

/* Retorna -1 cuando hay un error, 0 si todo OK*/
int	create_table(int argc, char **argv, t_table *table)
{
	if (argc == 6)
	{
		table->ends = 1;
		table->num_must_eat = ft_atoi(argv[5]);
	}
	table->ends = 0;
	table->stop = 1;
	table->num_phil = ft_atoi(argv[1]);
	table->mseg_die = ft_atoi(argv[2]);
	table->mseg_eat = ft_atoi(argv[3]);
	table->mseg_sleep = ft_atoi(argv[4]);
	if (table->num_phil <= 0 || table->num_phil > 300)
	{
		ft_exit_error("Number of philosophers must be in range [1,300]\n");	
		return (-1);
	}
	return (0);
}

int	create_mutex(t_table *table, t_threads *thread, int i)
{
	while (i < table->num_phil)
	{
		thread[i].id = i + 1;
		thread[i].n_meals = 0;
		thread[i].last_meal = get_actual_time();
		thread[i].table = table;
		if (pthread_mutex_init(&thread[i].right_fork, NULL))
			return (ft_exit_error("Error creating mutex\n"), -1);
		if (pthread_mutex_init(&thread[i].mutex_eat, NULL))
			return (ft_exit_error("Error creating mutex\n"), -1);
		if (i != 0)
			thread[i].left_fork = &thread[i - 1].right_fork;
		i++;
	}
	if (pthread_mutex_init(&thread->table->talk, NULL))
		return (ft_exit_error("Error creating mutex"), -1);
	if (pthread_mutex_init(&thread->table->stop_mutex, NULL))
		return (ft_exit_error("Error creating mutex"), -1);
	thread[0].left_fork = &thread[i - 1].right_fork;
	return (0);
}


/* Retorna 1 cuando hay un error, 0 si todo OK*/
int	check_input(int argc, char **argv, t_table *table, t_threads *thread)
{
	if (check_args(argc, argv) == -1)
		return (1);
	if (create_table(argc, argv, table) == -1)
		return (1);
	if (create_mutex(table, thread, 0) != 0)
		return (1);
	return (0);
}
