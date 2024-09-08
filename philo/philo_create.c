/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:51:13 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/07 17:27:09 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int	eating(t_philosopher *philo, t_main *main)
{
	int	total_meals;
	int	k;

	k = -1;
	total_meals = 0;
	while (++k < philo->main->num_philo)
	{
		pthread_mutex_lock(&philo->main->eating);
		if (philo[k].eaten == main->number_of_meals)
			total_meals++;
		if (total_meals >= main->num_philo)
		{
			pthread_mutex_unlock(&philo->main->eating);
			death(main);
			return (1);
		}
		pthread_mutex_unlock(&philo->main->eating);
	}
	return (0);
}

t_main	*start_info(t_main *main, char **av, int ac)
{
	if (!av)
		return (NULL);
	main = malloc(sizeof(t_main));
	if (!main)
		return (printf("struct allocation ERROR!\n"), NULL);
	main->num_philo = p_atoi(av[1]);
	main->life_time = p_atoi(av[2]);
	main->eat_time = p_atoi(av[3]);
	main->sleep_time = p_atoi(av[4]);
	main->number_of_meals = 0;
	if (ac == 6)
	{
		main->number_of_meals = p_atoi(av[5]);
		if (main->number_of_meals == 0)
			return (printf("Check number of meals\n"), NULL);
	}
	main->dead_or_alive = 1;
	main->philo = malloc(sizeof(t_philosopher) * main->num_philo);
	if (!main->philo)
		return (free(main), printf("philo allocation ERROR!\n"), NULL);
	main->right_fork = malloc(sizeof(pthread_mutex_t) * main->num_philo);
	if (!main->right_fork)
		return (free(main->philo), free(main),
			printf("fork allocation ERROR!\n"), NULL);
	return (main);
}

void	init_philo(t_main *main)
{
	int	k;

	k = -1;
	while (++k < main->num_philo)
	{
		main->philo[k].main = main;
		main->philo[k].last_eaten = get_time();
		main->philo[k].sleeping = 0;
		main->philo[k].dying = main->life_time;
		main->philo[k].eaten = 0;
	}
}

void	*life(void *data_struct)
{
	t_main			*main;
	t_philosopher	*philo;

	main = data_struct;
	philo = main->philo;
	while (1)
	{
		if (main->number_of_meals > 0 && eating(philo, main))
			return (NULL);
		if (monitoring(philo, main))
			return (NULL);
	}
	return (NULL);
}

int	philo_create(t_main *main)
{
	int			k;
	pthread_t	life_check;

	k = -1;
	init_philo(main);
	main->start_time = get_time();
	while (++k < main->num_philo)
	{
		main->philo[k].philosopher_id = k + 1;
		if (pthread_create(&main->philo[k].philo, NULL,
				routine, &main->philo[k]) != 0)
			return (1);
	}
	if (pthread_create(&life_check, NULL, life, main) != 0)
		return (1);
	if (pthread_join(life_check, NULL) != 0)
		return (printf("thread join ERROR!\n"), 1);
	return (0);
}
