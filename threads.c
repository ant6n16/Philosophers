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

void	*one_philo(void *arg)
{
	t_ph	*p;

	p = (t_ph *) arg;	
	printf_think(p);
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance == 1)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		usleep(1);
		pthread_mutex_lock(&p->eat_mtx);
		if ((ft_get_time() - p[0].when_last_eat) > p->table->msg_die)
			printf_die(p);
		pthread_mutex_unlock(&p->eat_mtx);
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_exit(NULL);
}

void	*philo_thread(void *arg)
{
	t_ph	*p;

	p = (t_ph *)arg;
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance == 1)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		eat(p);
		printf_sleep(p);
		ft_usleep(p->table->msg_sleep, p);
		if (p->table->msg_sleep == 0)
			usleep(1);
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
}
