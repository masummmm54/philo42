/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:04:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/14 13:45:25 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeper(long wait)
{
	long	begin;
	long	isenough;

	begin = get_time();
	while (1)
	{
		isenough = get_time() - begin;
		if (isenough >= wait)
			break ;
		usleep(250);
	}
}

void	eating(t_philo *philo)
{
	printer("is thinking", philo);
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	printer("has taken a fork", philo);
	pthread_mutex_lock(&philo->table->forks[philo->right]);
	printer("has taken a fork", philo);
	printer("is eating", philo);
	pthread_mutex_lock(&philo->table->time_lock);
	philo->last_meal = time_now(philo->table);
	pthread_mutex_unlock(&philo->table->time_lock);
	sleeper(philo->table->time_eat);
	pthread_mutex_unlock(&philo->table->forks[philo->right]);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
}

void	sleeps(t_philo *philo)
{
	printer("is sleeping", philo);
	sleeper(philo->table->time_sleep);
}

void	*thread_func(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	if (philo->table->nbr_philo == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		eating(philo);
		pthread_mutex_lock(&philo->table->eat_lock);
		philo->eat_count--;
		pthread_mutex_unlock(&philo->table->eat_lock);
		pthread_mutex_lock(&philo->table->dead_lock);
		if (philo->eat_count == 0 || philo->table->dead == false)
		{
			pthread_mutex_unlock(&philo->table->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->dead_lock);
		sleeps(philo);
	}
	return (NULL);
}
