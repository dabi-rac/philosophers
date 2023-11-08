/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:18:59 by dabi-rac          #+#    #+#             */
/*   Updated: 2023/11/08 23:25:31 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void* routine (void *arg)
{
    t_philo     *philo;
    philo = (t_philo *)arg;
    
    while (philo->data->dead == 0 && philo->data->finished == 0)
    {
        if (philo->id % 2 != 0)
            ft_usleep(1);
        its_my_life(philo);
    }
    return ((void *) 0);
}

void * control(void *arg)
{
    t_philo     *philo;
    philo = (t_philo *)arg;
    int     i;
    
    while(philo->data->dead == 0)
    {
        i = 0;
        while(i < philo->data->n_philos)
        {
            if(philo->data->philo[i].life_time <= get_time())
            {
                //printf("lifetime control = %llu, id = %d\n", philo->data->philo[i].life_time,  philo->data->philo[i].id);
                philo->data->dead = 1;
                message("died", &philo->data->philo[i]);
                break ;
            }
            i++;
   //         if(arg.times_to_eat)
    //        {
     //           while(arg.philo[i] > )
   //             arg.philo[i].meals >= arg.times_to_eat
   //         } 
        }
    }  
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
    if(philo->data->n_philos == 1)
    {
        ft_usleep(philo->data->time_to_die);
        return((void *) 0);
    }
	pthread_mutex_lock(philo->left);
	message("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
    message("is eating", philo);
    philo->life_time += philo->data->time_to_die;
    ft_usleep(philo->data->time_to_eat);
    philo->meals++;
	philo->eating = 1;
    pthread_mutex_unlock(&philo->lock);
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