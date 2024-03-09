/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:40 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/09 13:33:00 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef struct s_philo
{
	int					id;
	int					left;
	int					right;
	long				last_meal;
	t_table				*table;
}	t_philo;

struct s_table
{
	long				nbr_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				must_eat;
	long				day_start;
	bool				dead;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	t_philo				*philos;
};


void	init_table(char **av, t_table *table);
void	init_philo(t_philo *philo, int i);
void	init_launch(t_table *table);
void	*thread_func(void *table_t);
void	sleeper(t_philo *philo, long wait);
int		is_dead(t_philo *philo);

//utils
time_t	get_time(void);
void	printer(char *msg, t_philo *philo);
time_t	time_now(t_table *table);
void	ft_putendl_fd(char *s, int fd);
long	ft_atoi(const char *str);
int		check_args(char **av);
void	ft_error(char *msg);
void	ft_exit(t_philo *philo, int exit_code);
void	free_all(t_table *table);

#endif
