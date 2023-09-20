/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:22:22 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/19 19:27:16 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h> 

typedef struct table
{
	int				num_p;
	int				msg_die;
	int				msg_eat;
	int				msg_sleep;
	int				n_must_eat;
	int				now;
	int				advance;
	int				early_finish;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	advance_mtx;
	pthread_t		die_no_eat;
}				t_table;

typedef struct philo
{
	int					philo_dni;
	int					num_eats;
	int					when_last_eat;
	pthread_t			thread;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		eat_mtx;
	t_table				*table;
}				t_ph;

/* CHECK INPUT AND CREATE VARIABLES*/
int		check_arg(int argc, char **argv);
int		create_table(int argc, char **argv, t_table *table);
int		create_philo(t_table *table, t_ph *philos);

/* UTILS */
int		ft_atoi_philo(char *str);
void	print_all_info(t_table *table, t_ph *philo);
int	 	ft_get_time(void);
void	ft_usleep(int ms, t_ph *p);

/* PRINTS */
void	printf_fork(t_ph *p);
void	printf_eating(t_ph *p);
void	printf_sleep(t_ph *p);
void	printf_think(t_ph *p);
void	printf_die(t_ph *p);

/* THREADAS */
void	*philo_thread(void *arg);
void	ft_eating(t_ph *p);
void	one_philo(t_ph *p);
void	*check_thread(void	*param);
int		someone_die(t_ph *p);
int		check_n_meals(t_ph *p);
void	join_threads(t_ph *p);

#endif