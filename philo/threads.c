/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:47 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/05 12:04:42 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	life_check(t_main *main)
{
	pthread_mutex_lock(&main->life);
	if (main->dead_or_alive == 0)
	{
		pthread_mutex_unlock(&main->life);
		return (1);
	}
	pthread_mutex_unlock(&main->life);
	return (0);
}

void	*routine(void *philo_str)
{
	t_philosopher	*philo;

	philo = philo_str;
	if (philo->philosopher_id % 2 == 1)
		usleep(1000);
	while (!life_check(philo->main))
	{
		philo_eating(philo);
		if (philo->eaten == philo->main->number_of_meals)
			break ;
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

int	join_philo(t_main *main)
{
	int		k;

	k = -1;
	while (++k < main->num_philo)
	{
		if (pthread_join(main->philo[k].philo, NULL) != 0)
			return (printf("Threads not running\n"), 1);
	}
	return (0);
}

int	philo_start(t_main *main)
{
	if (philo_create(main))
		return (1);
	if (join_philo(main))
		return (1);
	return (0);
}
