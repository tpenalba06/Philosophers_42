/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steve_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:45:46 by npatron           #+#    #+#             */
/*   Updated: 2024/02/12 20:09:01 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "philo.h"

int     check_death(t_philo *philo, int i)
{
    if ((printf("%lld\n", (get_current_time() - philo[i].last_meal) >= (philo->data->tt_die))))
		return (0);
	else
		return (1);	
}

void	*meeting_security(void *ptr)
{
	t_philo	*philo;
	int	i;
	
	philo = (void *)ptr;
	while (1)
	{	
		i = 0;
		while (i < philo->data->nbr_philo - 1)
		{
			if (philo[i].eat == 1)
			{
				if (check_death(philo, i) == 0)
				{
					philo->dead = 1;
					printf("%d EST MORT\n", philo[i].id);
					return (NULL);
				}
			}
		i++;
		}
	}
}

void	last_fiesta(t_data *data)
{
	




	
}
