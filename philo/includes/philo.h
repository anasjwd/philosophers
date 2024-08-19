/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:43:57 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 03:50:59 by ajawad           ###   ########.fr       */
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

# define INVALID -42
# define TRUE 1

typedef struct s_philo
{
	pthread_t		id;
	int				number;
	unsigned int	num_of_meals;
	long			last_meal_time;
	pthread_mutex_t	*state_mutex;
	pthread_mutex_t	*fork;
}				t_philo;

typedef struct s_simulation_data
{
	unsigned int	num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_of_meals;
	int				start_time;
	int				sim_over;
	int				numof_philos_ended_eating;
	pthread_mutex_t	*sim_over_mutex;
	t_philo			**philos;
}				t_simulation_data;

t_simulation_data	**simulation_data(void);
int					*return_value(void);
int					monitor(void);
void				put_curr_state(int philo_number, char *msg);
void				msleep(size_t ms);
int					has_priority(t_philo *philo);

/*Parsing*/
int					check_num_of_arguments(int ac);
int					parsing(t_simulation_data *simulation_data, char **av,
						int ac);
int					handle_invalid_input(char *arg, char *msg);
int					ft_atoi(const char *nptr);

/*Printing*/
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);

/*Simulation*/
int					start_simulation(t_simulation_data *simulation_data);
/*--Routine*/
void				*routine(void *holder);
/*--Actions*/
int					ft_eat(t_philo *philo);
int					ft_think(t_philo *philo);
int					ft_sleep(t_philo *philo);

/*Utils*/
int					get_curr_time_ms(void);
long				get_time_from_start(void);

#endif
