/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:27 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/07 12:31:22 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free(t_main *main)
{
	if (main->philo)
		free(main->philo);
	if (main->right_fork)
		free(main->right_fork);
	if (main)
		free(main);
}

void	specific_condition(t_main *main)
{
	if (!main)
		return ;
	printf("\033[0;35m0 1 has taken a fork\n");
	my_usleep(main->life_time, main);
	printf("\033[0;35m%ld 1 died\n", main->life_time);
}

int	main(int ac, char **av)
{
	t_main	*main;

	main = NULL;
	if ((ac != 5 && ac != 6) || !av)
		return (printf("Check argument numbers!\n"), 1);
	if (av[1][0] <= '0')
		return (printf("Check philo number!\n"), 1);
	if (check_av(av) == 1)
		return (printf("argument must include numbers!\n"), 1);
	main = start_info(main, av, ac);
	if (!main)
		return (1);
	mutex_init(main);
	if (main->num_philo == 1)
		specific_condition(main);
	else if (main->num_philo > 1 && main->num_philo <= 200)
		philo_start(main);
	else
		printf("philo must be between 0 and 200\n");
	mutex_destroy(main);
	ft_free(main);
	return (0);
}
