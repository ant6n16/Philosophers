/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:22:22 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/14 19:22:36 by antdelga         ###   ########.fr       */
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
	long			now;
	short int		advance;
	short int		finish;
	pthread_mutex_t	speak;
	pthread_mutex_t	advance_mtx;
	pthread_t		starvation;
}				t_table;

typedef struct philo
{
	int					philo_dni;
	int					num_eats;
	int					when_last_eat;
	pthread_t			thread;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		mutex_eat;
	t_table				*table;
}				t_ph;

/* CHECK INPUT AND CREATE VARIABLES*/
int		check_arg(int argc, char **argv);
int		create_table(int argc, char **argv, t_table *table);
int		create_philo(t_table *table, t_ph *philos);

/* UTILS */
int		ft_atoi_philo(char *str);
int		ft_get_time(void);

/* PRINTS */
void	printf_fork(t_ph *p);
void	printf_eating(t_ph *p);
void	printf_sleep(t_ph *p);
void	printf_think(t_ph *p);
void	printf_die(t_ph *p);

/* THREADAS */
void	*one_philo(void *arg);
void	*check_one_philo_die(void *arg);

#endif