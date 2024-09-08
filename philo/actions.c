/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:10:24 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/05 12:07:12 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	philo_eating(t_philosopher *philo)
{
	mutex_lock_fork(philo);
	pthread_mutex_lock(&philo->main->eating);
	philo->last_eaten = get_time();
	philo->eaten++;
	message_writing(philo, 2);
	pthread_mutex_unlock(&philo->main->eating);
	my_usleep(philo->main->eat_time, philo->main);
	mutex_unlock_fork(philo);
	return (0);
}

int	philo_sleeping(t_philosopher *philo)
{
	if (life_check(philo->main))
		return (1);
	message_writing(philo, 3);
	my_usleep(philo->main->sleep_time, philo->main);
	return (0);
}

int	philo_thinking(t_philosopher *philo)
{
	if (life_check(philo->main))
		return (1);
	message_writing(philo, 4);
	usleep(200);
	return (0);
}

void	message_writing(t_philosopher *philo, int is_message)
{
	pthread_mutex_lock(&philo->main->life);
	if (is_message == 1 && philo->main->dead_or_alive == 1)
		printf ("\033[0;35m%ld %d has taken fork\n", get_time()
			- philo->main->start_time, philo->philosopher_id);
	else if (is_message == 2 && philo->main->dead_or_alive == 1)
		printf ("\033[0;35m%ld %d is eating\n", get_time()
			- philo->main->start_time, philo->philosopher_id);
	else if (is_message == 3 && philo->main->dead_or_alive == 1)
		printf ("\033[0;35m%ld %d is sleeping\n", get_time()
			- philo->main->start_time, philo->philosopher_id);
	else if (is_message == 4 && philo->main->dead_or_alive == 1)
		printf ("\033[0;35m%ld %d is thinking\n", get_time()
			- philo->main->start_time, philo->philosopher_id);
	else if (is_message == 5 && philo->main->dead_or_alive == 0)
		printf ("\033[0;35m%ld %d died\n", get_time()
			- philo->main->start_time, philo->philosopher_id);
	pthread_mutex_unlock(&philo->main->life);
}
