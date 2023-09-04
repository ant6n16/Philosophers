/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:19:01 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 19:15:11 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct table
{
	pthread_mutex_t	talk;
	pthread_mutex_t	stop_mutex;
	pthread_t		starvation;
	int				num_phil;
	int				mseg_die;
	int				mseg_eat;
	int				mseg_sleep;
	int				num_must_eat;
	long			actual_time;
	int				stop; /* Ver bien para qué, creo que para parar */
	int				ends; /* Ver bien para qué, creo que para nº comidas */
}				t_table;

typedef struct threads
{
	t_table				*table;
	pthread_t			thr;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		mutex_eat;
	int					id;
	int					n_meals;
	int					last_meal;
}				t_threads;

/* PARSE */
int		check_input(int argc, char **argv, t_table *table, t_threads *thread);
int		check_args(int argc, char **argv);
int		create_table(int argc, char **argv, t_table *table);
int		create_mutex(t_table *table, t_threads *thread, int i);

/* THREADS */
void	*one_philo(void *arg);
void	*mto_philo(void *arg);

/* UTILS */
int		get_actual_time(void);
int		ft_atoi(char *str);
void	ft_exit_error(char *s);
void	ft_usleep(int ms, t_threads *thread);
int		death_test(int i, t_threads *thread, int *flag);
int		food_test(t_threads *thread, int flag);
void	close_and_clean(t_threads *thread);
void	show_action(char *str, t_threads *thread);
void	*check_thread(void	*param);


#endif