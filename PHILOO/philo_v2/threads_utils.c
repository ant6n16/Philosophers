/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:24:38 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 21:35:33 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(int i, t_philos *philo, int *flag)
{
	int		time;

	while (++i < philo->data->n_philos)
	{
		pthread_mutex_lock(&philo[i].mutex_eat);
		pthread_mutex_lock(&philo->data->stop_mutex);
		time = timer() - philo[i].last_meal;
		if (time > philo[i].data->time_dead)
		{
			philo->data->stop = 0;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			pthread_mutex_unlock(&philo[i].mutex_eat);
			pthread_mutex_lock(&philo->data->talk);
			printf("(%ld) Philo %d is dead.\n", timer() - \
			philo->data->time_start, philo[i].id);
			pthread_mutex_unlock(&philo->data->talk);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (philo->data->ends == 1 && philo[i].n_meals < philo->data->n_eats)
			*(flag) = 1;
		pthread_mutex_unlock(&philo[i].mutex_eat);
	}
	return (1);
}

int	check_all_eat(t_philos *philo, int flag)
{
	if (philo->data->ends == 1 && flag == 0)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = 0;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_lock(&philo->data->talk);
		printf("All the philosophers have eaten!\n");
		pthread_mutex_unlock(&philo->data->talk);
		return (0);
	}
	return (1);
}

void	*check_thread(void	*param)
{
	int			i;
	t_philos	*philo;
	int			flag;

	philo = (t_philos *)param;
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		i = -1;
		flag = 0;
		usleep(10);
		if (check_death(i, philo, &flag) == 0)
			return (NULL);
		if (check_all_eat(philo, flag) == 0)
			return (NULL);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (NULL);
}

void	close_and_clean(t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->n_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(philo->data->starvation, NULL);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		pthread_mutex_destroy(&philo[i].fork_r);
		pthread_mutex_destroy(&philo[i].mutex_eat);
	}
	pthread_mutex_destroy(&philo->data->talk);
	pthread_mutex_destroy(&philo->data->stop_mutex);
}
