/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:45:58 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/15 16:15:07 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			mem_to_kernel(t_sdl *sdl, t_ray *ray, double *d_mem, int *i_mem)
{
	d_mem[0] = sdl->min_t;
	d_mem[1] = ray->dir.x;
	d_mem[2] = ray->dir.y;
	d_mem[3] = ray->dir.z;
	d_mem[4] = ray->orig.x;
	d_mem[5] = ray->orig.y;
	d_mem[6] = ray->orig.z;
	d_mem[7] = sdl->cam.rot.x;
	d_mem[8] = sdl->cam.rot.y;
	d_mem[9] = sdl->cam.rot.z;
	d_mem[10] = sdl->ambient;

	i_mem[0] = W_WIDTH;
	i_mem[1] = W_HEIGHT;
}

void			init_cl(t_cl *cl)
{
	int			fd;
	int			i;
	size_t		k_l;
	char		*k_s;
	int			error;
	char		test[1024];

	error = clGetPlatformIDs(0, NULL, &cl->num_platforms);
	printf("init cl %d\n", error);
	cl->plat_id = (cl_platform_id *)malloc(sizeof(cl_platform_id) * cl->num_platforms);
	error = clGetPlatformIDs(cl->num_platforms, cl->plat_id, NULL);
	clGetPlatformInfo(cl->plat_id[0], CL_PLATFORM_NAME, 1024, test, NULL);
	printf("platform id %s\n", test);
	error = clGetDeviceIDs(cl->plat_id[0], CL_DEVICE_TYPE_GPU, 0, NULL, &cl->num_device);
	cl->dev_id = (cl_device_id *)malloc(sizeof(cl_device_id) * cl->num_device);
	printf("num device %d\n", cl->num_device);
	error = clGetDeviceIDs(cl->plat_id[0], CL_DEVICE_TYPE_GPU, cl->num_device, cl->dev_id, NULL);
	clGetDeviceInfo(cl->dev_id[0], CL_DEVICE_NAME, 1024, test, NULL);
	printf("Device id %s\n", test);
	printf("clGetDeviceIDs %d\n", error);
	cl->context = clCreateContext(NULL, 1, cl->dev_id, NULL, NULL, &error);
	printf("clCreateContext %d\n", error);
	cl->queue = clCreateCommandQueue(cl->context, cl->dev_id[0], 0, &error);
	printf("CreateCommandQueue %d\n", error);
	fd = open("kernel.cl", O_RDONLY);
	k_s = (char*)malloc(sizeof(char) * 10000);
	i = read(fd, k_s, 10000);
	k_s[i] = '\0';
	k_l = ft_strlen(k_s);
	cl->prog = clCreateProgramWithSource(cl->context, 1,
	(const char**)&k_s, &k_l, &error);
	error = clBuildProgram(cl->prog, 1, cl->dev_id, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->prog, "start", &error);
	cl->obj_mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(t_cl_object) * cl->o_count, &cl->cl_obj, &error);
	cl->light_mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(t_cl_light) * cl->l_count, &cl->cl_light, &error);
	cl->img = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(int) * W_HEIGHT * W_WIDTH, NULL, &error);
	cl->i_mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(int) * 2, NULL, &error);	
	cl->d_mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(double) * 11, NULL, &error);
	error = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->obj_mem);
	error = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->light_mem);
	error = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->img);
	error = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->i_mem);
	error = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->d_mem);
}

void			start_kernel(t_cl *cl, t_sdl *sdl, t_ray *ray)
{
	int			err;
	size_t		gws;
	int			i_mem[2];
	double		d_mem[11];
	int			p_gws;
	int 		x;
	int			y;

	mem_to_kernel(sdl, ray, d_mem, i_mem);
	gws = W_WIDTH * W_HEIGHT;

	err = clEnqueueWriteBuffer(cl->queue, cl->i_mem, CL_TRUE, 0, sizeof(int) * 2, i_mem, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cl->queue, cl->d_mem, CL_TRUE, 0, sizeof(double) * 11, d_mem, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cl->queue, cl->obj_mem, CL_TRUE, 0, sizeof(t_cl_object) * cl->o_count, &cl->cl_obj, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cl->queue, cl->obj_mem, CL_TRUE, 0, sizeof(t_cl_light) * cl->l_count, &cl->cl_light, 0, NULL, NULL);
	
	err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL, &gws, NULL, 0, NULL, NULL);

	err = clEnqueueReadBuffer(cl->queue, cl->img, CL_TRUE, 0, sizeof(int) * gws, &cl->data, 0, NULL, NULL);

	p_gws = 0;
	while (p_gws < (int)gws)
	{
		x = p_gws % W_WIDTH;
		y = p_gws / W_WIDTH;
		SDL_SetRenderDrawColor(sdl->render, (cl->data[p_gws] & 0xFF0000), (cl->data[p_gws] & 0x00FF00), (cl->data[p_gws] & 0x0000FF), 255);
		SDL_RenderDrawPoint(sdl->render, x, y);
		p_gws++;	
	}
	
	//if (obj != NULL)
	//else 
		SDL_SetRenderDrawColor(sdl->render, 0, 0, 0, 255);

//	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
}