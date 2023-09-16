/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:55:06 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/16 20:49:11 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi_philo(char *str)
{
	long	number;
	int		i;

	number = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (printf("Only INT range values allowed\n"), -1);
	return (number);
}

int	ft_get_time(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

void	print_all_info(t_table *table, t_ph *philo)
{
	int	index;

	index = -1;
	printf("Num philo: %d\n", table->num_p);
	printf("Msg dead: %d\n", table->msg_die);
	printf("Msg eat: %d\n", table->msg_eat);
	printf("Msg sleep: %d\n", table->msg_sleep);
	printf("Msg sleep: %d\n", table->msg_sleep);
	printf("Num eats: %d\n", table->n_must_eat);
	printf("Now: %d\n", table->now);
	printf("Advance: %d\n", table->advance);
	printf("Finish: %d\n", table->finish);

	while (++index < table->num_p)
	{
		printf("Philo id: %d\n", philo[index].philo_dni);
		printf("Philo %d num eats: %d\n", index + 1, philo[index].num_eats);
		printf("Philo %d time last eat: %d\n", index + 1, philo[index].when_last_eat);
	}
}
