/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:45:46 by npatron           #+#    #+#             */
/*   Updated: 2024/02/13 20:37:29 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	message(philo, "is thinking");
}
void	sleeping(t_philo *philo)
{
	message(philo, "is sleeping");
	ft_usleep(philo->data->tt_sleep);
}

void	message(t_philo *philo, char *msg)
{
	
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n",(get_current_time() - philo->data->start_simulation), philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	uber_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if(dead_loop(philo) == 1)
    {
		pthread_mutex_unlock(philo->r_fork);
		last_fiesta(philo->data);
		return;
	}
	message(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	if(dead_loop(philo) == 1)
    {
		pthread_mutex_unlock(philo->l_fork); 
		last_fiesta(philo->data);
		return;
	}
	message(philo, "has taken a fork");
	philo->eat = 1;
	message(philo, "is eating");
	ft_usleep(philo->data->tt_eat);
	pthread_mutex_lock(&philo->data->eaten);	
	philo->eat_counting = philo->eat_counting + 1;
	pthread_mutex_unlock(&philo->data->eaten);	
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->eat = 0;
	pthread_mutex_lock(&philo->data->stop);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->stop);
}


void *routine(void *ptr)
{	
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		if(dead_loop(philo) == 1)
    	    break;
		uber_eats(philo);
		if(dead_loop(philo) == 1)
            break;
		sleeping(philo);
		if(dead_loop(philo) == 1)
            break;
		thinking(philo);
	}
	 if (pthread_join(philo->thread, NULL))
		return ((void *)1);
	return (ptr);
}

/*
thread par philo qui check si le philo qui lui est associe est mort. 
si le philo surveille est mort, le thread envoie un signal 
au mutex qui gere les messages et
 bloque pendant x temps l ecriture de tout les messages de tout les philos
 qund un meurt le checker envoie un mess a tout les autres checker que 
 c fini
*/

// void last_fiesta(t_data *data)
// {
// }

/*
forcer avec un booleen DEAD 1 ou 0 qui est change par steve jobs quand steve recoit l info que le philo est dead 
mettre la condition if(dead == 1) free all break je renvoie vers la fin de la boucle et ferme proprement 
je met la condition entre chaque ligne de uber eats, sleep et think entre chaque nmutex
tout les threads essayent d acceder a cette variable donc data race, du coup cette variable doit etre un mutex
pthtread_mutex_create(data->dead_lock)


ça dans steve jobs 

if(getcurrent time - last meal > time to die)
    dead == 1;


ça dans uber eats sleeping thinking
if(deadloop(philo) == 1)
    lastfiesta

int dead_loop(t_philo *philo)
{
    pthread_mutex_lock(&philo->data.dead_lock);
    if (philo->dead == 1)
        return (pthread_mutex_unlock(&philo->data.deadlock), 1);
    pthread_mutex_unlock(&philo.data->dead_lock);
    return (0);
}*/
