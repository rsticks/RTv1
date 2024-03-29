/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:20:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/14 18:27:58 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <OpenCL/opencl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>

# include "ftvector.h"
# include "libft.h"

# include <SDL2/SDL.h>

/*
** Size configuration
*/
# define W_WIDTH 	800
# define W_HEIGHT 	800

# define V_WIDTH 	40
# define V_HEIGHT 	40
/*
** Object name
*/
# define SPHERE "sphere:"
# define PLANE "plane:"
# define CYLINDER "cylinder:"
# define CONE "cone:"

# define CAMERA "cam:"

# define LIGHT "light:"

# define AMBIENT "ambient:"

/*
** Object id
*/
# define SPHERE_ID 1
# define PLANE_ID 2
# define CYLINDER_ID 3
# define CONE_ID 4

/*
** Help
*/
# define EPS 0.000001

typedef struct			s_cl
{
	cl_context			context;
	cl_command_queue	queue;
	cl_platform_id		*plat_id;
	cl_device_id		*dev_id;
	cl_uint				num_platforms;
	cl_uint				num_device;
	cl_kernel			kernel;
	cl_program			prog;
	cl_mem				obj_mem;
	cl_mem				light_mem;
	cl_mem				img;
	cl_mem				d_mem;
	cl_mem				i_mem;
	t_cl_object			*cl_obj;
	t_cl_light			*cl_light;
	int					*data;
	int 				o_count;
	int 				l_count;
}						t_cl;

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct s_color
{
	int r;
	int g;
	int b;
}				t_color;

typedef struct	s_output
{
	cl_int		r;
	cl_int		g;
	cl_int		b;
	cl_int		x;
	cl_int		y;
}				t_output;

/*
** pos - Camera position
** rot - Camera rotation
*/
typedef	struct		s_cam
{
	t_vector		pos;
	t_vector		rot;
}					t_cam;

/*
** orig - Camera position - start of ray
** dir - direction of the ray
*/
typedef	struct		s_ray
{
	t_vector		orig;
	t_vector		dir;
}					t_ray;

/*
** n - normal for current object
** p - ray for the camera to view point
*/
typedef	struct		s_light
{
	t_vector		pos;
	double			inten;
	t_color			col;

	t_vector		p;
	t_vector		n;

	double			new_inten;

	struct s_light	*next;
}					t_light;

/*
**  specular - зеркальность
*/
typedef struct		s_object
{
	t_vector		pos;
	t_vector		rot;
	t_color			col;
	double			r;
	int				name;

	double			specular;

	double			t;

	struct s_object	*next;
}					t_object;

typedef struct		s_cl_object
{
	
	cl_double			x_pos;
	cl_double			y_pos;
	cl_double			z_pos;
	cl_double			x_rot;
	cl_double			y_rot;
	cl_double			z_rot;
	cl_int				r_col;
	cl_int				g_col;
	cl_int				b_col;
	cl_double			r;
	cl_int				name;
	cl_double			specular;
	cl_double				t;
}					t_cl_object;

typedef	struct		s_cl_light
{
	cl_double			x_pos;
	cl_double			y_pos;
	cl_double			z_pos;
	cl_double			inten;
	cl_int				r_col;
	cl_int				g_col;
	cl_int				b_col;
	cl_double			x_p;
	cl_double			y_p;
	cl_double			z_p;
	cl_double			x_n;
	cl_double			y_n;
	cl_double			z_n;
	cl_double			new_inten;
}					t_cl_light;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	t_cam			cam;
	t_object		*obj;
	t_light			*light;

	int				obj_num; // Количество объектов в сцене
	int				light_num; // Количество источников света

	int				obj_counter;
	int				light_counter;

	t_object		*clos_obj;
	int				cam_is; // Существует ли камера
	double			min_t;

	double			ambient; //освещенность

	int				line_count; // количество линий в buf
	char			**scene; //храним сцену джля парсинга


}					t_sdl;

/*
** It's help you - http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
*/

t_cl_object		*transform_obj_data(t_object *obj, int *count);
t_cl_light		*transform_light_data(t_light *light, int *count);
void				init_cl(t_cl *cl);
void				events(t_ray ray, t_sdl sdl);
void 				scene_parser(t_sdl *sdl, char *scene_name);
int					kill_all(char *message);
void 				sdl_initialize(t_sdl *sdl);
double				get_quadratic_solution(double a, double b, double discriminant);
void 				free_mas(char **mas);

void 				object_parser(t_sdl *sdl, char **param);
void 				scene_parser(t_sdl *sdl, char *scene_name);

void 				init_camera(t_sdl *sdl, char **param);

void 				light(t_sdl *sdl, t_ray *ray);

t_vector 			get_sphere_normal(t_ray *ray, t_object *obj);
double 				get_sphere_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

t_vector 			get_plane_normal(t_ray *ray, t_object *obj);
double 				get_plane_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

t_vector 			get_cylinder_normal(t_ray *ray, t_object *obj);
double				get_cylinder_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

t_vector			get_cone_normal(t_ray *ray, t_object *obj);
double				get_cone_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

void				ray_tracing_init(t_sdl *sdl, t_ray *ray);
void				get_direction(t_point point, t_ray *ray, t_sdl *sdl);

t_point				init_point(double x, double y);

void				init_ambient(t_sdl *sdl, char **param);

void				string_parser(t_sdl *sdl);

int					ft_atoi_n(char *str, int *k);
t_light				*ft_add_light_link(t_sdl *sdl, t_light *link);
t_object			*ft_add_object_link(t_sdl *sdl, t_object *link);

void				ft_col_n_pos(t_sdl *sdl, t_object *link, int k);

void				ft_add_light(t_sdl *sdl, int *k, int ind);
void				ft_add_cyl_cone(t_sdl *sdl, int *k, int name, int ind);
void				ft_add_plane(t_sdl *sdl, int *k, int i);
void				ft_add_sphere(t_sdl *sdl, int *k, int i);

void				sphere_intersection(t_sdl *sdl, t_ray *camera, t_object *obj);
void				plane_intersection(t_sdl *sdl, t_ray *camera, t_object *obj);
void				cylinder_intersection(t_sdl *sdl, t_ray *camera, t_object *obj);
void				cone_intersection(t_sdl *sdl, t_ray *camera, t_object *obj);

void				check_object(t_sdl *sdl);



#endif