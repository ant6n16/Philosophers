/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:22:22 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 21:42:42 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct data
{
	int				n_philos;
	int				time_dead;
	int				time_eat;
	int				time_sleep;
	int				n_eats;
	short int		ends;
	short int		stop;
	long			time_start;
	pthread_mutex_t	talk;
	pthread_mutex_t	stop_mutex;
	pthread_t		starvation;
}				t_data;

typedef struct philo
{
	int					id;
	int					n_meals;
	int					last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		mutex_eat;
	t_data				*data;
}				t_philos;

/* INPUT */
int		check_args(int narg, char **argv);
int		check_input(int narg, char **argv, t_data *data, t_philos *philo);

/* UTILS */
void	ft_exit_error(char *msg);
int		timer(void);
void	ft_usleep(int ms, t_philos *philo);

/* THREADS */
void	*philo_thread(void *arg);
void	*check_thread(void	*param);
void	printf_mutex(char *str, t_philos *philo);
void	*exception(void *arg);
void	close_and_clean(t_philos *philo);

#endif