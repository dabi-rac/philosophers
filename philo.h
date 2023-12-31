/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:18:37 by dabi-rac          #+#    #+#             */
/*   Updated: 2023/11/08 22:21:27 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		controls;
	int				id;
	int				meals;
	int				eating;
	u_int64_t		life_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}		t_philo;

typedef struct s_data
{
	pthread_t		*thread;
	pthread_t		meals;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				dead;
	int				finished;
	u_int64_t		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	t_philo			*philo;
}		t_data;

int			check_args(const char *str);
int			storing(t_data *data);
int			init_table(t_data *data);
int			init(int ac, char **av, t_data *data);
int			init_thread(t_data *data);
void		*routine(void *arg);
void		*check_meals(void *arg);
void		*check_death(void *arg);
void		life_cycle(t_philo *philo);
void		message(char *str, t_philo *philo);
u_int64_t	get_time(void);
int			error(char *str, t_data *data, int flag);
void		clear_data(t_data *data);
void		ft_exit(t_data *data);
int			ft_usleep(u_int64_t time);
void * take_forks(t_philo *philo);
void * control(void *arg);
void * its_my_life(t_philo *philo);

#endif