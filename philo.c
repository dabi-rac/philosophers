/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:17:56 by dabi-rac          #+#    #+#             */
/*   Updated: 2023/11/04 21:48:29 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("arg devono essere 5 o 6");
		return (1);
	}
	if (init(ac, av, &data) == 1)
	{
		if (storing(&data) == 1)
		{
			if (init_table(&data) == 1)
			{
				if (init_thread(&data) == 1)
				{
					return (0);
				}
			}
		}
	}
	return (1);
}