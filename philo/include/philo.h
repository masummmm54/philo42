/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:40 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/14 13:23:43 by muhakose         ###   ########.fr       */
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

typedef pthread_mutex_t	t_mtx ;
typedef struct s_table	t_table ;

typedef struct s_philo
{
	int					id;
	int					left;
	int					right;
	int					eat_count;
	int					nbr_philo;
	long				last_meal;
	pthread_t			thread;
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
	pthread_t			monitor;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		time_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
};

//table
int		init_table(char **av, t_table *table);
void	init_philo(t_philo *philo, t_table *table, int i);
int		init_lunch(t_table *table);
int		init_mutex(t_table *table);
int		init_join(t_table *table);
int		thread_create(t_table *table);
void	*thread_func(void *philo_t);
void	*monitor(void *table_t);
void	sleeper(long wait);
int		is_dead(t_philo *philo);
int		check_dead(t_philo *philo, int flag);
int		all_full(t_table *table);
void	one_philo(t_philo *philo);

//utils
time_t	get_time(void);
void	printer(char *msg, t_philo *philo);
time_t	time_now(t_table *table);
void	ft_putendl_fd(char *s, int fd);
long	ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		check_args(char **av);
void	ft_error(char *msg);
void	ft_mutexit(t_table *table, int i, int flag);
void	free_all(t_table *table);

#endif
