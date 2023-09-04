/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:46:28 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 21:17:33 by antdelga         ###   ########.fr       */
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
	int				stop;
	int				ends;
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
}				t_th;

/* PARSE */
int		check_args(int argc, char **argv);
int		create_structs(int argc, char **argv, t_table *table, t_th *thread);
int		create_table(int argc, char **argv, t_table *table);
int		create_mutex(t_table *table, t_th *thread, int i);

/* THREADS */
void	*one_philo(void *arg);
void	*mto_philo(void *arg);

/* UTILS */
int		ft_atoi(char *str);
void	ft_exit_error(char *s);
int		get_actual_time(void);
void	show_action(char *str, t_th *thread);
void	ft_usleep(int ms, t_th *thread);
void	eat(t_th *thread);
void	*check_thread(void	*param);
int		death_test(int i, t_th *thread, int *flag);
int		food_test(t_th *thread, int flag);
void	close_and_clean(t_th *thread);

#endif