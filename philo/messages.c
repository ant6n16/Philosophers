/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:13:02 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/17 15:11:50 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printf_fork(t_ph *p)
{
	pthread_mutex_lock(&p->table->print_mtx);
	pthread_mutex_lock(&p->table->advance_mtx);
	if (p->table->advance == 1)
		printf("%d %d has taken a fork\n", ft_get_time() - p->table->now, \
		p->philo_dni);
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_mutex_unlock(&p->table->print_mtx);
}

void	printf_eating(t_ph *p)
{
	pthread_mutex_lock(&p->table->print_mtx);
	pthread_mutex_lock(&p->table->advance_mtx);
	if (p->table->advance == 1)
		printf("%d %d is eating\n", ft_get_time() - p->table->now, \
		p->philo_dni);
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_mutex_unlock(&p->table->print_mtx);
}

void	printf_sleep(t_ph *p)
{
	pthread_mutex_lock(&p->table->print_mtx);
	pthread_mutex_lock(&p->table->advance_mtx);
	if (p->table->advance == 1)
		printf("%d %d is sleeping\n", ft_get_time() - p->table->now, \
		p->philo_dni);
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_mutex_unlock(&p->table->print_mtx);
}

void	printf_think(t_ph *p)
{
	pthread_mutex_lock(&p->table->print_mtx);
	pthread_mutex_lock(&p->table->advance_mtx);
	if (p->table->advance == 1)
		printf("%d %d is thinking\n", ft_get_time() - p->table->now, \
		p->philo_dni);
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_mutex_unlock(&p->table->print_mtx);
}

void	printf_die(t_ph *p)
{
	pthread_mutex_lock(&p->table->print_mtx);
	pthread_mutex_lock(&p->table->advance_mtx);
	if (p->table->advance == 1)
		printf("%d %d died\n", ft_get_time() - p->table->now, p->philo_dni);
	p->table->advance = 0;
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_mutex_unlock(&p->table->print_mtx);
}
