/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:45:58 by rsticks           #+#    #+#             */
/*   Updated: 2019/11/13 18:37:37 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			init_cl(t_cl *cl, int o_count, int l_count)
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
	cl->obj_mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(t_cl_object) * o_count, NULL, &error);
	cl->light_mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(t_cl_light) * l_count, NULL, &error);
	cl->img = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(int) * W_WIDTH * W_HEIGHT, NULL, &error);
	error = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void*)&cl->obj_mem);
}

void			start_kernel(t_cl *cl, t_object *obj, t_sdl *sdl)
{
	int			err;
	double		dm[6];
	int			im[7];
	size_t		gws;
	int			x;
	int			y;

	gws = W_WIDTH * W_HEIGHT;

	err = clEnqueueWriteBuffer(cl->queue, cl->i_mem, CL_TRUE, 0, sizeof(int) * 7, im, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cl->queue, cl->d_mem, CL_TRUE, 0, sizeof(double) * 6, dm, 0, NULL, NULL);
	
	err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL, &gws, NULL, 0, NULL, NULL);

	err = clEnqueueReadBuffer(cl->queue, cl->img, CL_TRUE, 0, sizeof(int) * gws, f->mlx.data, 0, NULL, NULL);

	if (obj != NULL)
		SDL_SetRenderDrawColor(sdl->render, obj->col.r * p, obj->col.g * p, obj->col.b * p, 255);
	else
		SDL_SetRenderDrawColor(sdl->render, 0, 0, 0, 255);

	SDL_RenderDrawPoint(sdl->render, x, y);
//	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
}