/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:45:46 by npatron           #+#    #+#             */
/*   Updated: 2024/02/12 19:39:51 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	printf("%lld %d Tiens tiens........\n", (get_current_time() - philo->data->start_simulation), philo->id);
}
void	sleeping(t_philo *philo)
{
	printf("%lld %d ZZZZzzzzzZZZzzzzzZZZzzz\n", (get_current_time() - philo->data->start_simulation), philo->id);
	ft_usleep(philo->data->tt_sleep);
}

void	message(t_data *data, char *msg)
{
	pthread_mutex_lock(&data->print);
	printf("%lld %d %s\n",(get_current_time() - data->start_simulation), data->philo->id, msg);
	pthread_mutex_unlock(&data->print);
}

void	uber_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("%lld %d Coude droit sur la table\n", get_current_time()- philo->data->start_simulation, philo->id);
	pthread_mutex_lock(philo->l_fork);
	printf("%lld %d Coude gauche sur la table\n", get_current_time()- philo->data->start_simulation, philo->id);
	philo->eat = 1;
	printf("%lld %d MIAM MIAM\n",(get_current_time() - philo->data->start_simulation), philo->id);
	ft_usleep(philo->data->tt_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->eat = 0;
	philo->last_meal = get_current_time();
}


void *routine(void *ptr)
{	
	t_philo	*philo;
	
	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(1000);
	while (1 && philo->dead != 1)
	{
		uber_eats(philo);
		sleeping(philo);
		thinking(philo);
	}
	// if (pthread_join(philo, NULL))
	// 	return ((void *)1);
	return (ptr);
}

