/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:04:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/12 14:36:42 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeper(t_philo *philo, long wait)
{
	long	begin;
	long	isenough;

	pthread_mutex_lock(&philo->table->time_lock);
	begin = get_time();
	pthread_mutex_unlock(&philo->table->time_lock);
	while (1)
	{
		pthread_mutex_lock(&philo->table->time_lock);
		isenough = get_time() - begin;
		pthread_mutex_unlock(&philo->table->time_lock);
		if (isenough >= wait)
			break ;
		usleep(200);
	}
}

void	eating(t_philo *philo)
{
	if (check_dead(philo, 0))
		return ;
	printer("is thinking", philo);
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	if (check_dead(philo, 1))
		return ;
	printer("has taken a fork", philo);
	pthread_mutex_lock(&philo->table->forks[philo->right]);
	if (check_dead(philo, 2))
		return ;
	printer("has taken a fork", philo);
	printer("is eating", philo);
	pthread_mutex_lock(&philo->table->time_lock);
	philo->last_meal = time_now(philo->table);
	pthread_mutex_unlock(&philo->table->time_lock);
	sleeper(philo, philo->table->time_eat);
	pthread_mutex_unlock(&philo->table->forks[philo->right]);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
}

int	check_dead(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead == false)
	{
		if (flag == 0)
			pthread_mutex_unlock(&philo->table->dead_lock);
		if (flag == 1)
		{
			pthread_mutex_unlock(&philo->table->dead_lock);
			pthread_mutex_unlock(&philo->table->forks[philo->id]);
		}
		else if (flag == 2)
		{
			pthread_mutex_unlock(&philo->table->dead_lock);
			pthread_mutex_unlock(&philo->table->forks[philo->right]);
			pthread_mutex_unlock(&philo->table->forks[philo->id]);
		}
		return (true);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (false);
}

void	sleepandthink(t_philo *philo)
{
	printer("is sleeping", philo);
	sleeper(philo, philo->table->time_sleep);
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
		sleepandthink(philo);
	}
	return (NULL);
}
