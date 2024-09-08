/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_planning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:53:14 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/05 12:21:16 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/time.h>

long	get_time(void)
{
	struct timeval	start_time;
	long			curr;

	gettimeofday(&start_time, NULL);
	curr = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return (curr);
}

void	my_usleep(long parameter, t_main *dead_break)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < parameter)
	{
		pthread_mutex_lock(&dead_break->life);
		if (dead_break->dead_or_alive == 0)
		{
			pthread_mutex_unlock(&dead_break->life);
			break ;
		}
		pthread_mutex_unlock(&dead_break->life);
		usleep(100);
	}
}

int	monitoring(t_philosopher *philo, t_main	*main)
{
	int	i;

	i = -1;
	while (++i < philo->main->num_philo)
	{
		pthread_mutex_lock(&philo->main->eating);
		if (get_time() - philo[i].last_eaten >= main->life_time)
		{
			pthread_mutex_unlock(&philo->main->eating);
			death(main);
			message_writing(&philo[i], 5);
			return (1);
		}
		pthread_mutex_unlock(&philo->main->eating);
	}
	return (0);
}
