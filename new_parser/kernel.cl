/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:05:27 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/06 14:05:27 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct		s_ray
{
	double3			orig;
	double3			dir;
}					t_ray;

typedef struct		s_point
{
	double 			x;
	double 			y;
}					t_point;

typedef	struct		s_cam
{
	double3			pos;
	double3			rot;
}					t_cam;

double				RAD(double v)
{
	v = v (M_PI / 180);
	return(v);
}

double3				vec_rot_x(double3 v1, double alpha)
{
	double3			rot_vec;

	rot_vec.x = v1.x;
	rot_vec.y = v1.y * cos(alpha) - v1.z * sin(alpha);
	rot_vec.z = v1.y * sin(alpha) + v1.z * cos(alpha);
	return (rot_vec);
}

double3				vec_rot_xyz(double3 v1, double3 alp)
{
	v1 = vec_rot_x(v1, RAD(alp.x));
	v1 = vec_rot_x(v1, RAD(alp.y));
	v1 = vec_rot_x(v1, RAD(alp.z));
	return (v1);
}

t_point				init_point(double x, double y)
{
	t_point			point;

	point.x = x;
	point.y = y;
	return (point);
}


__kernel void 		start(__global )
{
	int				gid;
	int				x;
	int				y;
	double 			scaling_x;
	double			scaling_y;
	int				WIDTH;
	int				HEIGHT;
	int				V_WIDTH;
	int				V_HEIGHT;
	double2			point;
	t_ray			ray;
	int				obj_ind;

	gid = get_global_id(0);
	x = gid % WIDTH;
	y = gid / WIDTH;

	scaling_x = 2 * ((x + 0.5) / (double)W_WIDTH) - 1;
	scaling_y = 1 - 2 * ((y + 0.5) / (double)W_HEIGHT);

	point = (scaling_x, scaling_y);

	ray.dir.x = point.x * (V_WIDTH / (double)W_WIDTH);
	ray.dir.y = point.y * (V_HEIGHT / (double)W_HEIGHT);
	ray.dir.z = 1.0;
	ray.dir = vec_rot_xyz(ray.dir, cam->rot);

	obj_ind = 0;

}