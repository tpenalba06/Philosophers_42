/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steve_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:45:46 by npatron           #+#    #+#             */
/*   Updated: 2024/02/13 20:40:24 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "philo.h"

void	deunlock(t_philo *philo)
{
	int	i;

	i = 0;
	if(pthread_mutex_lock(philo->l_fork) == 0)
	{
		while (i < philo->data->nbr_philo)
		{
			pthread_mutex_unlock(philo[i].l_fork);
			i++;
		}
	}
}

void     check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop);
    if((get_current_time() - philo->last_meal) > (philo->data->tt_die / 1000) )
    {
		philo->data->dead = 1;
		
	}
	pthread_mutex_unlock(&philo->data->stop);
}

void    *meeting_security(void *ptr)
{
    t_philo *philo;
    int i;
    
    philo = (void *)ptr;
	i = 0;
    while (1)
    {   
        if (i == philo->data->nbr_philo)
            i = 0;
        check_death(&philo[i]);
        if(dead_loop(philo) == 1)
        {
			message(philo, "died");
			deunlock(philo);
            return(NULL);
        }
		if(c_fini(philo) == 0)
		{
			deunlock(philo);
			pthread_mutex_lock(&philo->data->deadlock);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->deadlock);
            return(NULL);
        }
		i ++;
	}
	return(0);
}

int	c_fini(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->eaten);	
	if (philo->data->nbr_meals == -1)
	{
		pthread_mutex_unlock(&philo->data->eaten);
		return (1);
	}
	while(i < philo->data->nbr_philo)
	{
		if(philo[i].eat_counting < philo->data->nbr_meals)
		{
			pthread_mutex_unlock(&philo->data->eaten);
			return(1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->eaten);
	return(0);
}
int dead_loop(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->deadlock);
    if (philo->data->dead == 1)
    {
		return(pthread_mutex_unlock(&philo->data->deadlock), 1);
	}
	pthread_mutex_unlock(&philo->data->deadlock);
    return (0);
}

void	last_fiesta(t_data *data)
{
	{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(data->philo[i].l_fork);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->deadlock);
	pthread_mutex_destroy(&data->eaten);
	}
}
















//si un philo meurt il doit liberer tout ses mutex
/*
int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->info->dead);
	if (nb)
		philo->info->stop = 1;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->t_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_eat >= (long)(philo->info->t_die))
	{
		pthread_mutex_unlock(&philo->info->eat);
		pthread_mutex_unlock(&philo->info->stop);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->eat);
	pthread_mutex_unlock(&philo->info->stop);
	return (NULL);
}
	
}
*/