/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:44:59 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 17:23:15 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo, int *first_fork, int *second_fork)
{
	int	temp;

	*first_fork = philo->number - 1;
	*second_fork = philo->number % (*simulation_data())->num_of_philos;
	if ((unsigned)(philo->number) == (*simulation_data())->num_of_philos)
	{
		temp = *first_fork;
		*first_fork = *second_fork;
		*second_fork = temp;
	}
}

int	take_forks(t_philo *philo, int first_fork, int second_fork)
{
	while (!has_priority(philo))
		usleep(100);
	pthread_mutex_lock((*simulation_data())->philos[first_fork]->fork);
	if (simulation_is_over())
	{
		pthread_mutex_unlock((*simulation_data())->philos[first_fork]->fork);
		return (1);
	}
	put_curr_state(philo->number, "has taken a fork");
	while (!has_priority(philo))
		msleep(1);
	pthread_mutex_lock((*simulation_data())->philos[second_fork]->fork);
	if (simulation_is_over())
	{
		pthread_mutex_unlock((*simulation_data())->philos[first_fork]->fork);
		pthread_mutex_unlock((*simulation_data())->philos[second_fork]->fork);
		return (1);
	}
	put_curr_state(philo->number, "has taken a fork");
	return (0);
}

int	ft_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (simulation_is_over())
		return (1);
	get_forks(philo, &first_fork, &second_fork);
	if (take_forks(philo, first_fork, second_fork))
		return (1);
	put_curr_state(philo->number, "is eating");
	pthread_mutex_lock(philo->state_mutex);
	philo->num_of_meals++;
	philo->last_meal_time = get_time_from_start();
	pthread_mutex_unlock(philo->state_mutex);
	msleep((*simulation_data())->time_to_eat);
	pthread_mutex_unlock((*simulation_data())->philos[second_fork]->fork);
	pthread_mutex_unlock((*simulation_data())->philos[first_fork]->fork);
	if (simulation_is_over())
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (simulation_is_over())
		return (1);
	put_curr_state(philo->number, "is sleeping");
	msleep((*simulation_data())->time_to_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (simulation_is_over())
		return (1);
	put_curr_state(philo->number, "is thinking");
	return (0);
}
