/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:04:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/09 13:32:50 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeper(t_philo *philo, long wait)
{
	long	begin;

	wait /= 1000;
	begin = get_time();
	while(1)
	{
		if (is_dead(philo))
			ft_exit(philo, EXIT_FAILURE);
		if (get_time() - begin >= wait)
			break ;
		usleep(100);
	}
}

void	ft_exit(t_philo *philo, int exit_code)
{
	free_all(philo->table);
	exit(exit_code);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	printer("has taken a fork", philo);
	if (philo->table->nbr_philo != 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		printer("has taken a fork", philo);
		printer("is eating", philo);
		philo->last_meal = time_now(philo->table);
		sleeper(philo, philo->table->time_eat);
		pthread_mutex_unlock(&philo->table->forks[philo->right]);
	}
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
}

void	sleepandthink(t_philo *philo)
{
	printer("is sleeping", philo);
	sleeper(philo, philo->table->time_sleep);
	printer("is thinking", philo);
}

int	is_dead(t_philo *philo)
{
	bool	how_long;

	pthread_mutex_lock(&philo->table->dead_mtx);
	how_long = time_now(philo->table) - philo->last_meal > philo->table->time_die / 1000;
	if (how_long)
	{
		printf("%lu %d dead\n", time_now(philo->table), philo->id + 1);
		philo->table->dead = false;
		return (true);
	}
	pthread_mutex_unlock(&philo->table->dead_mtx);
	return (false);
}

void	*thread_func(void *table_t)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)table_t;
	i = philo->table->must_eat;
	if (philo->id % 2 != 0)
		sleepandthink(philo);
	while(philo->table->dead)
	{
		eating(philo);
		i--;
		if (i == 0)
			break;
		if (philo->table->dead)
			sleepandthink(philo);
	}
	return (NULL);
}
