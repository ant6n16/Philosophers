/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:59:59 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 21:15:41 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *arg)
{
	t_th	*threads;

	threads = (t_th *) arg;
	if (threads->table->num_phil == 1)
	{
		show_action("is thinking", threads);
		pthread_mutex_lock(&threads->table->stop_mutex);
		while (threads->table->stop == 1)
		{
			pthread_mutex_unlock(&threads->table->stop_mutex);
			usleep(1);
			pthread_mutex_lock(&threads->table->stop_mutex);
		}
		pthread_mutex_unlock(&threads->table->stop_mutex);
	}
	pthread_exit(NULL);
}

void	eat(t_th *thread)
{
	if (thread->id % 2 == 1)
	{
		pthread_mutex_lock(&thread->right_fork);
		show_action("has taken a fork", thread);
		pthread_mutex_lock(thread->left_fork);
		show_action("has taken a fork", thread);
	}
	else
	{
		pthread_mutex_lock(thread->left_fork);
		show_action("has taken a fork", thread);
		pthread_mutex_lock(&thread->right_fork);
		show_action("has taken a fork", thread);
	}
	pthread_mutex_lock(&thread->mutex_eat);
	show_action("is eating", thread);
	thread->last_meal = get_actual_time();
	thread->n_meals++;
	pthread_mutex_unlock(&thread->mutex_eat);
	ft_usleep(thread->table->mseg_eat, thread);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(&thread->right_fork);
}

void	*mto_philo(void *arg)
{
	t_th	*threads;

	threads = (t_th *)arg;
	pthread_mutex_lock(&threads->table->stop_mutex);
	while (threads->table->stop == 1)
	{
		pthread_mutex_unlock(&threads->table->stop_mutex);
		eat(threads);
		show_action("is sleaping", threads);
		ft_usleep(threads->table->mseg_sleep, threads);
		if (threads->table->mseg_sleep == 0)
			usleep(1);
		show_action("is thinking", threads);
		pthread_mutex_lock(&threads->table->stop_mutex);
	}
	pthread_mutex_unlock(&threads->table->stop_mutex);
	pthread_exit(NULL);
}

void	*check_thread(void	*param)
{
	int		i;
	t_th	*thread;
	int		flag;

	thread = (t_th *)param;
	pthread_mutex_lock(&thread->table->stop_mutex);
	while (thread->table->stop)
	{
		pthread_mutex_unlock(&thread->table->stop_mutex);
		i = -1;
		flag = 0;
		usleep(10);
		if (death_test(i, thread, &flag) == 0)
			return (NULL);
		if (food_test(thread, flag) == 0)
			return (NULL);
		pthread_mutex_lock(&thread->table->stop_mutex);
	}
	pthread_mutex_unlock(&thread->table->stop_mutex);
	return (NULL);
}
