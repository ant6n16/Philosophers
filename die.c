/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:00:19 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/16 21:37:33 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_one_philo_die(void *arg)
{
	t_ph	*philo;

	philo = (t_ph *) arg;
	if (ft_get_time() > philo[0].table->msg_die)
	{
		printf("Entre\n");
		pthread_mutex_lock(&philo->table->advance_mtx);
		philo->table->advance = 0;
		pthread_mutex_unlock(&philo->table->advance_mtx);
		pthread_mutex_lock(&philo->table->speak);
		printf("%d %d is dead\n", ft_get_time(), philo[0].philo_dni);
		pthread_mutex_unlock(&philo[0].table->speak);
		pthread_exit(NULL);
	}
	pthread_exit(NULL);
}
