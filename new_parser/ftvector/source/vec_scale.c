/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:26:36 by daron             #+#    #+#             */
/*   Updated: 2019/10/19 13:28:41 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvector.h"

t_vector	vec_scale(t_vector v1, double factor)
{
	v1.x *= factor;
	v1.y *= factor;
	v1.z *= factor;
	return (v1);
}
