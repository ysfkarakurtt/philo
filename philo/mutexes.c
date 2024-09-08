/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:09:17 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/07 17:36:36 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	death(t_main *main)
{
	pthread_mutex_lock(&main->life);
	main->dead_or_alive = 0;
	pthread_mutex_unlock(&main->life);
}

int	mutex_lock_fork(t_philosopher *phi)
{
	int	right_fork;
	int	left_fork;

	right_fork = phi->philosopher_id % phi->main->num_philo;
	left_fork = (phi->philosopher_id + 1) % phi->main->num_philo;
	if (right_fork < left_fork)
	{
		pthread_mutex_lock(&phi->main->right_fork[left_fork]);
		message_writing(phi, 1);
		pthread_mutex_lock(&phi->main->right_fork[right_fork]);
		message_writing(phi, 1);
	}
	else
	{
		pthread_mutex_lock(&phi->main->right_fork[right_fork]);
		message_writing(phi, 1);
		pthread_mutex_lock(&phi->main->right_fork[left_fork]);
		message_writing(phi, 1);
	}
	return (0);
}

void	mutex_unlock_fork(t_philosopher *phi)
{
	int	left_fork;
	int	right_fork;

	right_fork = phi->philosopher_id % phi->main->num_philo;
	left_fork = (phi->philosopher_id + 1) % phi->main->num_philo;
	pthread_mutex_unlock(&phi->main->right_fork[right_fork]);
	pthread_mutex_unlock(&phi->main->right_fork[left_fork]);
}

int	mutex_init(t_main *main)
{
	int	k;

	k = -1;
	while (++k < main->num_philo)
	{
		if (pthread_mutex_init(&main->right_fork[k], NULL) != 0)
			return (printf("fork mutex ERROR!\n"), 1);
	}
	if (pthread_mutex_init(&main->life, NULL) != 0)
		return (printf("life mutex ERROR!\n"), 1);
	if (pthread_mutex_init(&main->eating, NULL) != 0)
		return (printf("eating mutex ERROR!\n"), 1);
	return (0);
}

int	mutex_destroy(t_main *main)
{
	int	k;

	k = -1;
	while (++k < main->num_philo)
	{
		if (pthread_mutex_destroy(&main->right_fork[k]) != 0)
			return (printf("fork mutex destro ERROR!\n"), 1);
	}
	if (pthread_mutex_destroy(&main->life) != 0)
		return (printf("life mutex destroy ERROR!\n"), 1);
	if (pthread_mutex_destroy(&main->eating) != 0)
		return (printf("eating mutex destroy ERROR!\n"), 1);
	return (0);
}
