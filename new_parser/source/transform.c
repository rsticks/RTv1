/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:32:59 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/15 16:16:48 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_cl_object		*transform_obj_data(t_object *obj, int *count)
{
	t_cl_object *cl_obj;
	t_object	*past_obj;

	past_obj = obj;
	count = 0;
	while(obj)
	{
		count++;
		obj = obj->next;
	}
	cl_obj = (t_cl_object*)malloc(sizeof(t_cl_object) * *count);
	count = 0;
	obj = past_obj;
	while (obj)
	{
		cl_obj[*count].x_pos = obj->pos.x;
		cl_obj[*count].y_pos = obj->pos.y;
		cl_obj[*count].z_pos = obj->pos.z;
		cl_obj[*count].x_rot = obj->rot.x;
		cl_obj[*count].y_rot = obj->rot.y;
		cl_obj[*count].z_rot = obj->rot.z;
		cl_obj[*count].r_col = obj->col.r;
		cl_obj[*count].g_col = obj->col.g;
		cl_obj[*count].b_col = obj->col.b;
		cl_obj[*count].r = obj->r;
		cl_obj[*count].name = obj->name;
		cl_obj[*count].specular = obj->specular;
		cl_obj[*count].t = obj->t;
		count++;
		obj = obj->next;
	}
	return(cl_obj);
}

t_cl_light		*transform_light_data(t_light *light, int *count)
{
	t_cl_light	*cl_light;
	t_light		*p_light;

	p_light = light;
	count = 0;
	while (light)
	{
		count++;
		light = light->next;
	}
	cl_light = (t_cl_light*)malloc(sizeof(t_cl_light) * *count);
	count = 0;
	while (p_light)
	{
		cl_light[*count].x_pos = p_light->pos.x;
		cl_light[*count].y_pos = p_light->pos.y;
		cl_light[*count].z_pos = p_light->pos.z;
		cl_light[*count].inten = p_light->inten;
		cl_light[*count].r_col = p_light->col.r;
		cl_light[*count].g_col = p_light->col.g;
		cl_light[*count].b_col = p_light->col.b;
		cl_light[*count].x_p = p_light->p.x;
		cl_light[*count].y_p = p_light->p.y;
		cl_light[*count].z_p = p_light->p.z;
		cl_light[*count].x_n = p_light->n.x;
		cl_light[*count].y_n = p_light->n.y;
		cl_light[*count].z_n = p_light->n.z;
		cl_light[*count].new_inten = p_light->new_inten;
		count++;
		p_light = p_light->next;
	}
	return(cl_light);
}