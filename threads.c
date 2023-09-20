/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:09:43 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/19 19:27:46 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo(t_ph *p)
{
	pthread_mutex_unlock(&p->fork_r);
	pthread_exit(NULL);
}

void	ft_eating(t_ph *p)
{
	if (!(p->philo_dni % 2))
	{
		pthread_mutex_lock(p->fork_l);
		printf_fork(p);
		pthread_mutex_lock(&p->fork_r);
		printf_fork(p);
	}
	else
	{
		pthread_mutex_lock(&p->fork_r);
		printf_fork(p);
		
		if (p->table->num_p == 1)
			one_philo(p);
		pthread_mutex_lock(p->fork_l);
		printf_fork(p);
	}
	pthread_mutex_lock(&p->eat_mtx);
	printf_eating(p);
	p->when_last_eat = ft_get_time();
	p->num_eats++;
	pthread_mutex_unlock(&p->eat_mtx);
	ft_usleep(p->table->msg_eat, p);
	pthread_mutex_unlock(p->fork_l);
	pthread_mutex_unlock(&p->fork_r);
}

void	*philo_thread(void *arg)
{
	t_ph	*p;

	p = (t_ph *)arg;
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance == 1)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		ft_eating(p);
		printf_sleep(p);
		ft_usleep(p->table->msg_sleep, p);
		printf_think(p);
		pthread_mutex_lock(&p->table->advance_mtx);
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_exit(NULL);
}

void	join_threads(t_ph *p)
{
	int	i;

	i = -1;
	while (++i < p->table->num_p)
		pthread_join(p[i].thread, NULL);
	pthread_join(p->table->die_no_eat, NULL);
	i = -1;
	while (++i < p->table->num_p)
	{
		pthread_mutex_destroy(&p[i].fork_r);
		pthread_mutex_destroy(&p[i].eat_mtx);
	}
	pthread_mutex_destroy(&p->table->print_mtx);
	pthread_mutex_destroy(&p->table->advance_mtx);
	free(p);
}
