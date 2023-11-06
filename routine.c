/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:18:59 by dabi-rac          #+#    #+#             */
/*   Updated: 2023/11/06 23:24:43 by dabi-rac         ###   ########.fr       */
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
        return ((void *) 1);
    }
    	while (philo->data->dead == 0 && philo->data->finished == 0)
            its_my_life(philo);
            
    return ((void *) 0);
}

void * controls(void *arg)
{
    t_philo     *philo;
    philo = (t_philo *)arg;
    int     i;
    
    while(arg.dead == 0)
    {
        i = 0;
        while(i++ < arg->n_philos)
        {
            if(arg.philo[i]->life_time <= get_time())
            {
                philo->data->dead = 1;
                message("died",philo);
                break ;
            }
            i = 0;
   //         if(arg.times_to_eat)
    //        {
     //           while(arg.philo[i] > )
   //             arg.philo[i].meals >= arg.times_to_eat
   //         }
            
        }
    }
    
    
    /*
    write the meal and death controls
    */
   return((void *) 0);
}

void * its_my_life(t_philo *philo)
{
    take_forks(philo);
    message("is sleeping",philo);
    ft_usleep(philo->data->time_to_sleep);
    message("is thinking",philo);
    return ((void *) 0);
}

void * take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->right);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->left);
	message("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->lock);
    message("is eating", philo);
    ft_usleep(philo->data->time_to_eat);
    philo->meals++;
	philo->eating = 1;
	philo->life_time += philo->data->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
    pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
    return((void *) 0);
}

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d %s\n", (get_time() - philo->data->start), \
	philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->write);
}