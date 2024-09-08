/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:36 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/05 12:07:12 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_main
{
	struct s_philosopher	*philo;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			life;
	pthread_mutex_t			eating;
	long					start_time;
	long					life_time;
	long					eat_time;
	long					sleep_time;
	int						num_philo;
	int						number_of_meals;
	int						dead_or_alive;
}	t_main;

typedef struct s_philosopher
{
	pthread_t			philo;
	struct s_main		*main;
	int					philosopher_id;
	int					eaten;
	long				last_eaten;
	long				sleeping;
	long				dying;
}	t_philosopher;

void		ft_free(t_main *main);
void		my_usleep(long parameter, t_main *dead_break);
void		death(t_main *main);
void		mutex_unlock_fork(t_philosopher *philo);
void		*routine(void *philo_str);
void		message_writing(t_philosopher *philo, int is_message);
int			check_av(char **av);
int			p_atoi(char *s1);
int			mutex_lock_fork(t_philosopher *philo);
int			life_check(t_main *main);
int			philo_start(t_main *main);
int			philo_create(t_main *main);
int			philo_eating(t_philosopher *philo);
int			philo_sleeping(t_philosopher *philo);
int			philo_thinking(t_philosopher *philo);
int			mutex_init(t_main *main);
int			mutex_destroy(t_main *main);
int			monitoring(t_philosopher *philo, t_main	*main);
long		get_time(void);
t_main		*start_info(t_main *main, char **av, int ac);

#endif
