/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:20:54 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/29 09:24:27 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_curr_state(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->stats_mutex);
	philo->last_meal_time = get_curr_time();
	philo->numof_meals++;
	pthread_mutex_unlock(philo->stats_mutex);
	if (print_curr_state(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	if (print_curr_state(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	msleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (print_curr_state(philo, "is sleeping"))
		return (1);
	msleep(philo->data->time_to_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (print_curr_state(philo, "is thinking"))
		return (1);
	return (0);
}

void	*routine(void *holder)
{
	t_philo	*philo;

	philo = (t_philo *)holder;
	if (philo->number % 2 == 0)
		msleep(60);
	while (TRUE)
	{
		if (ft_eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_think(philo))
			return (NULL);
		msleep((philo->data->time_to_die - (get_curr_time() - philo->last_meal_time)) / 2);
	}
	return (NULL);
}
