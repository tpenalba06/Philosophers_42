/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:10:10 by npatron           #+#    #+#             */
/*   Updated: 2024/02/13 18:35:25 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>


typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat;
	int				eat_counting;
	long long unsigned int			last_meal;
	
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
    int 			nbr_philo;
    long long unsigned int 	tt_die;
    int 			tt_eat;
    int 			tt_sleep;
	int 			nbr_meals;
	
    long long 		start_simulation;
	bool			dead;
	pthread_t		steve_jobs;
	pthread_mutex_t *forks;
	pthread_mutex_t stop;
	pthread_mutex_t print;
	pthread_mutex_t eaten;
	pthread_mutex_t	deadlock;
	t_philo 		*philo;
}			t_data;

int			lil_atoi(char *s);
int			print_error(int i);
int			check_args(char **tab, int a, t_data *data);
void		init_struct(t_data *data);
long long	get_current_time(void);
int			ft_usleep(long long milliseconds);
void 		*routine(void *ptr);
void 		start(t_data *data);
void		message(t_philo *philo, char *msg);
void		thinking(t_philo *philo);
void		*meeting_security(void *ptr);
int 		dead_loop(t_philo *philo);
void		last_fiesta(t_data *data);
int			c_fini(t_philo *philo);
#endif