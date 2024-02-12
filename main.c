/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:10:07 by npatron           #+#    #+#             */
/*   Updated: 2024/02/12 17:49:10 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data	*data;
    t_philo *philo;
	//int i = 0;
	data = malloc(sizeof(t_data));
    if(data == NULL)
        perror("erreur d'allocation");
    philo = NULL;
    if (!check_args(argv, argc, data))
    {
        data->philo = malloc(sizeof(t_philo) * data->nbr_philo);
        start(data);
    }
    (void)philo;
    //if( ++i < data->nbr_philo) 
      //  pthread_join(data->philo[i].thread, NULL);
   // sleep(10);
    return (0);
}