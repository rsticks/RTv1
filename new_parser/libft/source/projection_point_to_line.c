/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_point_to_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:35:25 by daron             #+#    #+#             */
/*   Updated: 2019/10/11 16:41:05 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	projection_point_to_line(double start, double end, double persent)
{
	return (start + ((end - start) * persent));
}
