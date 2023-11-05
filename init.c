/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:32:20 by dabi-rac          #+#    #+#             */
/*   Updated: 2023/11/05 18:38:23 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(int ac, char **av, t_data *data)
{
	data->n_philos = check_args(av[1]);
	data->time_to_die = check_args(av[2]);
	data->time_to_eat = check_args(av[3]);
	data->time_to_sleep = check_args(av[4]);
	if (ac == 6)
		data->times_to_eat = check_args(av[5]);
	else
		data->times_to_eat = -1;
	if (data->n_philos < 1 || data->n_philos > 200 || data->time_to_die < 0 || \
	data->time_to_eat < 0 || data->time_to_sleep < 0 || data->times_to_eat < -1)
		return (0);
	data->time_to_die = (u_int64_t)data->time_to_die;
	data->time_to_eat = (u_int64_t)data->time_to_eat;
	data->time_to_sleep = (u_int64_t)data->time_to_sleep;
	data->dead = 0;
	data->finished = 0;
	data->start = get_time();
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (1);
}

int	check_args(const char *str)
{
	long	n;
	int		s;
	int		i;

	n = 0;
	s = 1;
	i = 0;
	if (str[i] == '-')
		n *= -1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (error(NULL, NULL, 1));
		n = n * 10;
		n = n + str[i] - '0';
		i++;
	}
	if ((n * s) > 2147483647 || (n * s) < -2147483648)
		return (error(NULL, NULL, 1));
	n = (int)n;
	return (n * s);
}

int	storing(t_data *data)
{
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data->n_philos);
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	data->thread = (pthread_t *)malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->forks || !data->philo || !data->thread)
		return (error("Errore Allocazione", data, 0));
	return (1);
}

int	init_table(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->philo[i].data = data;
		data->philo[i].id = i;
		data->philo[i].meals = 0;
		data->philo[i].eating = 0;
		data->philo[i].life_time = get_time() + data->time_to_die;
		pthread_mutex_init(&data->philo[i].lock, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
	}
	data->philo[0].left = &data->forks[0];
	data->philo[0].right = &data->forks[data->n_philos - 1];
	i = 1;
	while (i < data->n_philos)
	{
		data->philo[i].left = &data->forks[i];
		data->philo[i].right = &data->forks[i - 1];
		i++;
	}
	return (1);
}

int	init_thread(t_data *data)
{
	pthread_t	td_meals;
	int			i;

	i = -1;
	/*
	if (data->times_to_eat > 0)
	{
		if (pthread_create(&td_meals, NULL, &check_meals, data) != 0)
			return (error("Errore nella creazione thread di controllo", data, 0));
		pthread_join(td_meals, NULL);
	}
	*/
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->thread[i], NULL, &routine, &data->philo[i]) != 0)
			return (error("Errore nella creazione thread di routine", data, 0));
		pthread_detach(data->thread[i]);
		ft_usleep(1);
	}
	while (data->dead == 0 && data->finished == 0)
		;
	ft_exit(data);
	return (1);
}