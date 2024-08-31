/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:13:35 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/29 14:42:41 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>

# define TRUE 1
# define INVALID -42
# define UNAVAILABLE -1

typedef struct s_philo
{
	pthread_t		id;
	int				number;
	int				numof_meals;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*stats_mutex;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				numof_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				numof_meals;
	int				sim_over;
	long			start_time;
	pthread_mutex_t	*printing_mutex;
	pthread_mutex_t	*sim_over_mutex;
	t_philo			**philos;
}				t_data;

void	ft_putstr_fd(char *str, int fd);
void	msleep(size_t ms);
void	*routine(void *holder);
void	*alloc(size_t size);
void	monitor(t_data *data);
void	destroy_philos(t_philo **philos);
void	print_death_msg(t_philo *philo);
long	get_curr_time(void);
int		initializing(t_data *data);
int		print_curr_state(t_philo *philo, char *state);
int		parsing(int ac, char **av, t_data *data);
int		check_numof_args(int ac);
int		initialize(t_data *data);
int		start_simulation(t_data *data);
int		simulation_is_over(t_philo *philo);

#endif
