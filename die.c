/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:00:19 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/19 19:30:24 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* int	check_death(t_ph *p)
{
	int	time;
    int i;

    i = -1;
	while (++i < p->table->num_p)
	{
		pthread_mutex_lock(&p[i].eat_mtx);
		time = ft_get_time() - p[i].when_last_eat;
		if (time > p[i].table->msg_die)
		{
			pthread_mutex_lock(&p->table->advance_mtx);
			p->table->advance = 0;
			pthread_mutex_unlock(&p->table->advance_mtx);
			pthread_mutex_unlock(&p[i].eat_mtx);
			printf_die(p);
            return (0);
		}
	}
	return (1);
}

void	*check_thread(void	*param)
{
	t_ph	*p;

	p = (t_ph *)param;
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance == 1)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		usleep(10);
		if (check_death(p))
			return (NULL);
        if (p->table->early_finish == 1)
        {
            pthread_mutex_lock(&p->table->advance_mtx);
            p->table->advance = 0;
            pthread_mutex_unlock(&p->table->advance_mtx);
            return (NULL);
        }
		pthread_mutex_lock(&p->table->advance_mtx);
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	return (NULL);
} */

void	eat(t_ph *p)
{
	if (p->philo_dni % 2 == 1)
	{
		pthread_mutex_lock(&p->fork_r);
		printf_fork(p);
		pthread_mutex_lock(p->fork_l);
		printf_fork(p);
	}
	else
	{
		pthread_mutex_lock(p->fork_l);
		printf_fork(p);
		pthread_mutex_lock(&p->fork_r);
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

int	check_death(int i, t_ph *p, int *flag)
{
	int		time;

	while (++i < p->table->num_p)
	{
		pthread_mutex_lock(&p[i].eat_mtx);
		pthread_mutex_lock(&p->table->advance_mtx);
		time = ft_get_time() - p[i].when_last_eat;

		if (time > p[i].table->msg_die)
		{
			p->table->advance = 0;
			pthread_mutex_unlock(&p->table->advance_mtx);
			pthread_mutex_unlock(&p[i].eat_mtx);
			pthread_mutex_lock(&p->table->print_mtx);
			printf("%d %d is dead\n", ft_get_time() - \
			p->table->now, p[i].philo_dni);
			pthread_mutex_unlock(&p->table->print_mtx);
			return (0);
		}
		pthread_mutex_unlock(&p->table->advance_mtx);
		if (p->table->early_finish == 1 && p[i].num_eats < p->table->n_must_eat)
			*(flag) = 1;
		pthread_mutex_unlock(&p[i].eat_mtx);
	}
	return (1);
}

int	check_all_eat(t_ph *p, int flag)
{
	if (p->table->early_finish == 1 && flag == 0)
	{
		pthread_mutex_lock(&p->table->advance_mtx);
		p->table->advance = 0;
		pthread_mutex_unlock(&p->table->advance_mtx);
		pthread_mutex_lock(&p->table->print_mtx);
		printf("All the philosophers have eaten!\n");
		pthread_mutex_unlock(&p->table->print_mtx);
		return (0);
	}
	return (1);
}

void	*check_thread(void	*param)
{
	int		i;
	t_ph	*p;
	int		flag;

	p = (t_ph *)param;
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		i = -1;
		flag = 0;
		usleep(10);
		if (check_death(i, p, &flag) == 0)
			return (NULL);
		if (check_all_eat(p, flag) == 0)
			return (NULL);
		pthread_mutex_lock(&p->table->advance_mtx);
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	return (NULL);
}

