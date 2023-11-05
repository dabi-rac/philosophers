/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:18:59 by dabi-rac          #+#    #+#             */
/*   Updated: 2023/11/05 19:23:56 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void* routine (void *arg)
{
    t_philo     *philo;
    philo = (t_philo *)arg;
    if(philo)
    {
        pthread_create(&philo->controls, NULL, &controls, NULL);
    }
    else
    {
        error("Errore nella crazione thread di controllo", philo->data, 0);
        return(1);
    }
    	while (philo->data->dead == 0 && philo->data->finished == 0)
            its_my_life(philo);
}

void* controls(void *arg)
{
    /*
    write the meal and death controls
    */
}

void * its_my_life(t_philo *philo)
{
    take_forks(philo);
    eat();
    put_back_forks();
}

void * take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->right);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->left);
	message("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->lock);
    philo->meals++;
	philo->eating = 1;
	philo->life_time = get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
	message("is eating", philo);
}